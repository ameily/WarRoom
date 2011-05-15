/*
    This file is part of the War Edit application (waredit)
    Url: https://github.com/ameily/WarRoom
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


WarPage::WarPage(Game& game) : m_root(), m_id(game.id()), m_name(game.name())
{
    m_rules = &game;
    m_race = 0;
    
    QList<Rule*> rules = game.rules();
    int len = rules.length();
    qSort(rules.begin(), rules.end(), compareRule);
    
    initPage(game.name());
    HtmlNode body("body");
    body.append(wrapTitle(game.name(), Page));
    /*
    HtmlNode toc("ul");
    toc.style("border: 1px solid #000000; padding-top: 10px; padding-bottom: 10px; padding-right: 10px");
    for(int i = 0; i < len; i++)
    {
        toc.append(
            HtmlNode("li").append(
                HtmlNode("a", rules[i]->name()).href("#" + rules[i]->id())
            )
        );
    }
    */
    /*body.append(
        HtmlNode("div").append(
            HtmlNode("h1", game.name())
        ).append(
            HtmlNode("div").append(
                game.id(), true
            ).append(
                HtmlNode("br")
            ).append(
                game.book(), true
            ).append(
                HtmlNode("br")
            ).append(
                game.edition() + " Edition", true
            ).append(
                HtmlNode("br")
            ).append(
                game.version(), true
            )
        )
    );*/
    
    HtmlNode ruleList("div");
    //ruleList.append(HtmlNode("h2", "Rule List"));
    //ruleList.style("margin-left: 20px");
    
    
    for(int i = 0; i < len; i++)
    {
        ruleList.append(convertToHtmlNode(*rules[i], Section));//.style("margin-bottom: 40px"));
        ruleList.append(HtmlNode("br"));
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



WarPage::HtmlNode WarPage::convertToHtmlNode(const IRule& rule, int level)
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
    
    if(level != Inline && level != Page && desc.length() > maxDescLength)
    {
        int cutoff;
        for(cutoff = maxDescLength; cutoff > 0 && !desc[cutoff].isSpace(); cutoff--);
        
        cutoff++;
        
        HtmlNode more("a", "more...");
        more.href("rule://" + rule.id() + "?name=" + rule.name());
        desc = desc.left(cutoff) + more.toHtml();
    }
    
    convertToHtml(desc);
    ret.append(desc, false);
    
    return ret;
}

void WarPage::convertToHtml(QString& out)
{
    out.replace("[lb]", "<br/>");
    out.replace("[p]", "<br/><br/>");
    
    out.replace("[b]", "<strong>");
    out.replace("[/b]", "</strong>");
    
    out.replace("[i]", "<em>");
    out.replace("[/i]", "</em>");
    
    convertReferences(out);
}

void WarPage::convertReferences(QString& out)
{
    QRegExp re("\\[\\[\\s*(\\w+)\\s*\\|*([^\\|\\]]*)\\]\\]");
    int pos = 0;
    
    while((pos = re.indexIn(out, pos)) >= 0)
    {
        ReferenceString r;
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
        
        r.prefix = "";
        r.title = "";
        
        HtmlNode refnode = resolveReference(r);
        QString replace = refnode.toHtml();
        out.replace(pos, re.matchedLength(), replace);
        pos += replace.length();
    }
}

WarPage::HtmlNode WarPage::resolveReference(WarPage::ReferenceString& ref)
{
    HtmlNode ret;
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
                ref.prefix = "unit";
                name = unit->name();
            }
        }
        else
        {
            ref.prefix = "wargear";
            name = wargear->name();
        }
    }
    else if(rule)
    {
        ref.prefix = "rule";
        name = rule->name();
        ref.title = rule->brief();
    }
    
    if(name.isEmpty())
        ref.name = "";
    else if(ref.name.isEmpty())
        ref.name = name;
    else if(ref.name == "plural")
        ref.name = (name[name.length() - 1] == 's' ? name : name + "s");
    
    if(!ref.prefix.isEmpty())
    {
        ret = HtmlNode("a", ref.name);
        ret.href(ref.prefix + "://" + ref.id + "?name=" + ref.name);
        if(!ref.title.isEmpty())
            ret.title(ref.title);
    }
    else
    {
        qDebug() << "ref lookup failed: " << ref.id;
        qDebug() << (m_rules->resolveRuleReference(ref.id) == 0);
        qDebug() << (m_rules->getRule(ref.id) == 0);
        ret = HtmlNode("span");
        ret.style("color: #ff0000; text-decoration: underline");
        if(ref.name.isEmpty())
            ret.append(ref.id, true);
        else
            ret.append(ref.name, true);
    }
    
    return ret;
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
        tag = "strong";
    
    HtmlNode node(tag, title);
    if(level == SubSection || level == Section)
        node.style("margin-bottom:0px; padding-bottom:0px");
    
    
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

WarPage::HtmlNode::HtmlNode() : m_body(), m_tag(), m_id(), m_href(), m_style(),
    m_title()
{

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


