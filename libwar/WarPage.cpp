/*
    This file is part of the War Room project
    https://github.com/ameily/WarRoom
    Copyright (C) 2011  Adam Meily <meily.adam@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "WarPage.h"
#include <QTextDocument>
#include <QUrl>
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include <qtextdocument.h>


WarPage::WarPage(Game& game) : m_id(game.id()), m_name(game.name()), m_root()
{
    m_rules = &game;
    m_race = 0;
    
    initPage(game.name());
    
    QList<Rule*> rules = game.rules();
    int len = rules.length();
    qSort(rules.begin(), rules.end(), compareRule);
    
    HtmlNode body("body");
    body.append(wrapTitle(game.name(), Page));
    
    HtmlNode ruleList("div");
    for(int i = 0; i < len; i++)
    {
        ruleList.append(convertToHtmlNode(*rules[i], Section));
        //ruleList.append(HtmlNode("br"));
    }
    
    body.append(ruleList);
    m_root.append(body);
}

WarPage::WarPage(const IRule& rule, RuleList& list, Race *race) : m_id(rule.id()),
    m_name(rule.name())
{
    m_rules = &list;
    m_race = race;
    initPage(rule.name());
    HtmlNode body("body");
    body.append(convertToHtmlNode(rule, Page));
    m_root.append(body);
}

WarPage::WarPage(const WarPage& other) : m_root(other.m_root),
    m_name(other.m_name), m_id(other.m_id)
{
    m_race = other.m_race;
    m_rules = other.m_rules;
}

WarPage& WarPage::operator=(const WarPage& other)
{
    m_root = other.m_root;
    m_id = other.m_id;
    m_name = other.m_name;
    m_race = other.m_race;
    m_rules = other.m_rules;
}

QString WarPage::defaultStyleSheet() const
{
    return  "h1 { margin-bottom: 20px; }\n"
            "h2 { margin-bottom: 15px; }\n"
            "h3 { margin-bottom: 10px; }\n"
            //"p { text-indent: 15px; }\n"
            "a { text-decoration: none; }";
}



Race* WarPage::race()
{
    return m_race;
}

RuleList* WarPage::ruleList()
{
    return m_rules;
}

const QString& WarPage::id() const
{
    return m_id;
}

const QString& WarPage::name() const
{
    return m_name;
}

int WarPage::maxDescriptionLength() const
{
    return 512;
}



WarPage::HtmlNode WarPage::convertToHtmlNode(const IRule& rule, NodeLevel level)
{
    int maxDescLength = 512;
    HtmlNode ret("div");
    ret.append(
        HtmlNode("a").id(rule.id()).append(
            wrapTitle(rule.name(), level)
        )
    );
    
    QString desc;
    
    if(level != Inline)
        desc = Qt::escape(rule.description());
    
    if(desc.isEmpty())
        desc = Qt::escape(rule.brief());
    
    cutOff(level, RulePrefix, rule.id(), rule.name(), desc);
    
    convertToHtml(desc, ret);
    return ret;
}

void WarPage::cutOff(NodeLevel level, ReferencePrefix prefix, const QString& id,
    const QString& name, QString& out)
{
    if(level != Inline && level != Page && out.length() > maxDescriptionLength())
    {
        ReferenceString ref;
        ref.prefix = prefix;
        ref.id = id;
        ref.name = name;
        ref.title = "";
        
        int cutoff;
        for(cutoff = maxDescriptionLength(); cutoff > 0 && !out[cutoff].isSpace(); cutoff--);
        
        cutoff++;
        
        HtmlNode more("a");
        more.append("[more &rarr;]", false);
        more.href(ref);
        out = out.left(cutoff) + more.toHtml();
    }
}


void WarPage::convertToHtml(QString& out, WarPage::HtmlNode& parent)
{
    out.replace("[lb]", "<br/>");
    //out.replace("[p]", "");
    
    out.replace("[b]", "<b>");
    out.replace("[/b]", "</b>");
    
    out.replace("[i]", "<i>");
    out.replace("[/i]", "</i>");
    
    convertReferences(out);
    
    QStringList paras = out.split("[p]");
    int len = paras.length();
    for(int i = 0; i < len; i++)
        parent.append(HtmlNode("p").append(paras[i], false));
}

void WarPage::convertReferences(QString& out)
{
    QRegExp re("\\[\\[\\s*(\\w+)\\s*\\|*([^\\|\\]]*)\\]\\]");
    int pos = 0;
    
    while((pos = re.indexIn(out, pos)) >= 0)
    {
        ReferenceString r;
        r.prefix = NullPrefix;
        r.title = "";
        
        if(!re.cap(2).trimmed().isEmpty())
        {
            r.id = re.cap(1).trimmed();
            r.name = re.cap(2).trimmed();
        }
        else
        {
            r.id = re.cap(1).trimmed();
            //qDebug() << "matched id: " << r.id;
            r.name = "";
        }
        
        HtmlNode refnode = resolveReference(r);
        QString replace = refnode.toHtml();
        out.replace(pos, re.matchedLength(), replace);
        pos += replace.length();
    }
}

WarPage::HtmlNode WarPage::resolveReference(WarPage::ReferenceString& ref)
{
    QString name;
    const Rule *rule = m_rules->resolveRuleReference(ref.id);
    if(m_race && !rule)
    {
        Wargear *wargear = m_race->getWargear(ref.id);
        if(!wargear)
        {
            Unit *unit  = m_race->getUnit(ref.id);
            if(unit)
            {
                ref.prefix = UnitPrefix;
                name = unit->name();
            }
        }
        else
        {
            ref.prefix = WargearPrefix;
            name = wargear->name();
        }
    }
    else if(rule)
    {
        ref.prefix = RulePrefix;
        name = rule->name();
        ref.title = rule->brief();
    }
    
    if(name.isEmpty())
        ref.name = "";
    else if(ref.name.isEmpty())
        ref.name = name;
    else if(ref.name == "plural")
        ref.name = (name[name.length() - 1] == 's' ? name : name + "s");
    
    HtmlNode node(ref);
    
    return node;
}



WarPage::HtmlNode WarPage::wrapTitle(const QString& title, int level) const
{
    QString tag;
    QString style;
    if(level == Page)
        tag = "h1";
    else if(level == Section)
        tag = "h2";
    else if(level == SubSection)
        tag = "h3";
    else if(level == Inline)
        tag = "b";
    
    HtmlNode node(tag, title);
    
    return node;
}

void WarPage::initPage(const QString& title)
{
    m_root = WarPage::HtmlNode("html").append(
        HtmlNode("head").append(
            HtmlNode("title", title)
        )
    );
}


QString WarPage::toHtml() const
{
    return m_root.toHtml();
}

QString WarPage::wrapWhiteSpaceTags(const QDomElement& ele)
{
    QString ret = ele.text().simplified();
    ret.replace("[lb]", "[lb]\n");
    ret.replace("[p]", "\n[p]\n");
    ret.replace("\n ", "\n");
    
    return ret;
}



WarPage::HtmlNode::HtmlNode(const QString& tag, const QString& body) : m_body(),
    m_tag(tag), m_id(), m_href(), m_style(), m_title()
{
    m_body = Qt::escape(body);
}

WarPage::HtmlNode::HtmlNode(const WarPage::HtmlNode& other) : 
    m_body(other.m_body), m_tag(other.m_tag), m_id(other.m_id),
    m_href(other.m_href), m_style(other.m_style), m_title(other.m_style)
{

}

WarPage::HtmlNode::HtmlNode(const WarPage::ReferenceString& ref,
    const QString& name) : m_body(), m_tag(), m_id(), m_href(), m_style(),
    m_title()
{
    QString finalName;
    if(name.isEmpty() && ref.name.isEmpty())
        finalName = ref.id;
    else if(name.isEmpty())
        finalName = ref.name;
    else
        finalName = name;
    
    if(ref.prefix == WarPage::NullPrefix)
    {
        m_tag = "span";
        m_style = "color: #ff0000;";
    }
    else
    {
        m_tag = "a";
        href(toString(ref.prefix) + "://" + ref.id + "?name=" + finalName);
    }
    
    append(finalName, true);
    
    if(!ref.title.isEmpty())
        m_title = Qt::escape(ref.title);
}


WarPage::HtmlNode::HtmlNode() : m_body(), m_tag(), m_id(), m_href(), m_style(),
    m_title()
{

}

QString WarPage::HtmlNode::toString(WarPage::ReferencePrefix prefix)
{
    QString str;
    if(prefix == WarPage::RulePrefix)
        str = "rule";
    else if(prefix == WarPage::WargearPrefix)
        str = "wargear";
    else if(prefix == WarPage::UnitPrefix)
        str = "unit";
    else
        str = "unresolved";
    
    return str;
}

WarPage::HtmlNode& WarPage::HtmlNode::href(const WarPage::ReferenceString& ref)
{
    href(toString(ref.prefix) + "://" + ref.id + "?name=" + ref.name);
}



WarPage::HtmlNode& WarPage::HtmlNode::operator=(const WarPage::HtmlNode& other)
{
    m_body = other.m_body;
    m_href = other.m_href;
    m_id = other.m_id;
    m_style = other.m_style;
    m_tag = other.m_tag;
    m_title = other.m_title;
}


WarPage::HtmlNode& WarPage::HtmlNode::append(const WarPage::HtmlNode& tag)
{
    m_body += tag.toHtml();
    return *this;
}

WarPage::HtmlNode& WarPage::HtmlNode::append(const QString& txt, bool escape)
{
    if(escape)
        m_body += Qt::escape(txt);
    else
        m_body += txt;
    
    return *this;
}


WarPage::HtmlNode& WarPage::HtmlNode::href(const QString& href)
{
    m_href = QUrl(href).toEncoded();
    return *this;
}

WarPage::HtmlNode& WarPage::HtmlNode::id(const QString& id)
{
    m_id = Qt::escape(id);
    return *this;
}

WarPage::HtmlNode& WarPage::HtmlNode::style(const QString& style)
{
    m_style = Qt::escape(style);
    return *this;
}

WarPage::HtmlNode& WarPage::HtmlNode::title(const QString& title)
{
    m_title = Qt::escape(title);
    return *this;
}

QString WarPage::HtmlNode::toHtml() const
{
    QString node = "<" + m_tag;
    if(!m_id.isEmpty())
        node += " id=\"" + m_id + "\"";
    
    if(!m_href.isEmpty())
        node += " href=\"" + m_href + "\"";
    
    if(!m_style.isEmpty())
        node += " style=\"" + m_style + "\"";
    
    if(!m_title.isEmpty())
        node += " title=\"" + m_title + "\"";
    
    if(m_body.isEmpty())
        node += " />";
    else
        node += ">" + m_body + "</" + m_tag + ">";
    
    return node;
}


