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
    qSort(rules.begin(), rules.end(), compareRulePtr);
    
    HtmlNode body("body");
    body.append(wrapTitle(game.name(), PageNode));
    
    HtmlNode ruleList("div");
    for(int i = 0; i < len; i++)
        append(ruleList, *rules[i], EntityNode | BriefDescription);
    
    body.append(ruleList);
    m_root.append(body);
}

WarPage::WarPage(Race& race) : m_id(race.id()), m_root(),
    m_name(race.name())
{
    m_rules = &race;
    m_race = &race;
    HtmlNode body("body");
    initPage(race.name() + " -- Unit List");
    QString subtitle;
    int len;
    
    /*if(mode == RuleListMode)
    {
        
    }
    else if(mode == WargearListMode)
    {
    }
    else // Unit List
    {*/
        //subtitle = "Unit List";
        body.append(wrapTitle(race.name(), PageNode));
        QList<Unit*> units = m_race->units();
        qSort(units.begin(), units.end(), compareUnit);
        len = units.length();
        
        for(int i = 0; i < len; i++)
            append(body, *units[i], EntityNode | BriefDescription);
    //}
    
    
    m_root.append(body);
}


WarPage::WarPage(const IRule& rule, RuleList& list, Race *race) : m_id(rule.id()),
    m_name(rule.name())
{
    m_rules = &list;
    m_race = race;
    initPage(rule.title());
    HtmlNode body("body");
    append(body, rule, PageNode);
    m_root.append(body);
}

WarPage::WarPage(const IWargear& wargear, Race& race) : m_id(wargear.id()),
    m_name(wargear.name())
{
    m_rules = &race;
    m_race = &race;
    initPage(wargear.title());
    HtmlNode body("body");
    append(body, wargear, PageNode);
    m_root.append(body);
    qDebug() << "end of WarPage()";
}

WarPage::WarPage(const Unit& unit, Race& race) : m_id(unit.id()), m_name(unit.name())
{
    m_rules = &race;
    m_race = &race;
    initPage(unit.name());
    HtmlNode body("body");
    append(body, unit, PageNode);
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
            "h3 { margin-bottom: 0px; padding-bottom: 0px; }\n"
            "p { text-indent: 15px; margin-top: 0px; }\n"
            "a { text-decoration: none; }\n"
            "td, th { padding-left: 0.5em; padding-right: 0.5em; }";
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

WarPage::HtmlNode WarPage::resolveReference(WarPage::MarkupReference& ref)
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



WarPage::HtmlNode WarPage::wrapTitle(const QString& title, NodeOptions opts) const
{
    QString tag;
    QString style;
    if(opts.testFlag(PageNode))
        tag = "h1";
    else if(opts.testFlag(EntityNode))
        tag = "h2";
    else
        tag = "h3";
    
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

QString WarPage::markupFromXml(const QDomElement& ele)
{
    return ele.text().trimmed();
}

WarPage::MarkupReference WarPage::toRef(const IRule& rule)
{
    MarkupReference ref;
    ref.id = rule.id();
    ref.name = rule.name();
    ref.title = rule.brief();
    ref.prefix = RulePrefix;
    
    return ref;
}

WarPage::MarkupReference WarPage::toRef(const IWargear& wargear)
{
    MarkupReference ref;
    ref.id = wargear.id();
    ref.name = wargear.name();
    ref.title = wargear.title();
    ref.prefix = WargearPrefix;
    return ref;
}

WarPage::MarkupReference WarPage::toRef(const Unit& unit)
{
    MarkupReference ref;
    ref.id = unit.id();
    ref.name = unit.name();
    ref.title = "Page " + unit.page();
    ref.prefix = UnitPrefix;
    return ref;
}




WarPage::NodeOptions WarPage::childOptions(WarPage::NodeOptions opts)
{
    NodeOptions ret;
    if(opts.testFlag(PageNode))
        ret |= EntityNode;
    else if(opts.testFlag(EntityNode))
        ret |= InlineNode;
    else
        ret |= InlineNode;
    
    if(opts.testFlag(BriefDescription))
        ret |= BriefDescription;
    
    return ret;
}





void WarPage::append(WarPage::HtmlNode& parent, const IRule& rule, NodeOptions opts)
{
    int max = 512;
    if(!opts.testFlag(InlineNode))
    {
        parent.append(wrapTitle(rule.title(), opts));
        
        QString body = Qt::escape(
            rule.description().isEmpty() ? rule.brief() : rule.description()
        );
        
        if(opts.testFlag(BriefDescription) && body.length() > max)
            cutoff(body, toRef(rule), max);
        
        append(parent, body, opts);
    }
    else
    {
        parent.append(
            HtmlNode(toRef(rule))
        );
    }
    
}

void WarPage::append(WarPage::HtmlNode& parent, const Unit& unit, WarPage::NodeOptions opts)
{
    if(opts.testFlag(InlineNode))
    {
        parent.append(
            HtmlNode(toRef(unit))
        );
    }
    else
    {
        QList<WargearRef> wargears = unit.wargearRefs();
        QList<RuleRef> rules = unit.ruleRefs();
        qSort(wargears.begin(), wargears.end(), compateWargearRef);
        qSort(rules.begin(), rules.end(), compareRuleRef);
        
        NodeOptions children = childOptions(opts);
        NodeOptions attachments = childOptions(children);
        parent.append(wrapTitle(unit.name(), opts));
        append(parent, unit.profile());
        
        int len = wargears.length();
        if(len > 0)
        {
            HtmlNode list("ul");
            parent.append(wrapTitle("Wargears", children));
            for(int i = 0; i < len; i++)
            {
                HtmlNode node("li");
                append(node, wargears[i], attachments);
                list.append(node);
            }
            parent.append(list);
        }
        
        len = rules.length();
        if(len > 0)
        {
            HtmlNode list("ul");
            parent.append(wrapTitle("Rules", children));
            for(int i = 0; i < len; i++)
            {
                HtmlNode node("li");
                append(node, rules[i], attachments);
                list.append(node);
            }
            parent.append(list);
        }
        
    }
    
}

void WarPage::append(WarPage::HtmlNode& parent, const UnitProfile& profile)
{
    HtmlNode table("table");
    UnitProfile::Characteristics list = profile.characteristics();
    
    int unitCount = list.unit.count();
    int vehicleCount = list.vehicle.count();
    int columns = unitCount + vehicleCount;
    int start = vehicleCount > 0 ? 0 : 1;
    for(int row = start; row < 3; row++)
    {
        HtmlNode tr("tr");
        for(int col = 0; col < columns; col++)
        {
            UnitProfile::Characteristic current = col < unitCount ? 
                list.unit[col] : list.vehicle[col - unitCount];
            
            if(row == 0)
            {
                if(col < unitCount)
                    tr.append(HtmlNode("th").align("center").append("&nbsp;", false));
                else if(col == unitCount)
                {
                    tr.append(
                        HtmlNode("th", "ARMOUR").colspan(
                            QString::number(vehicleCount)
                        ).align("center")
                    );
                }
            }
            else if(row == 1)
                tr.append(HtmlNode("th", current.key).align("center"));
            else if(row == 2)
                tr.append(HtmlNode("td", current.value).align("center"));
        }
        table.append(tr);
    }
    
    parent.append(table);
}

void WarPage::append(WarPage::HtmlNode& parent, const IWargear& wargear, NodeOptions opts)
{
    if(opts.testFlag(InlineNode))
    {
        parent.append(
            HtmlNode(toRef(wargear))
        );
    }
    else
    {
        NodeOptions children = childOptions(opts);
        QList<WargearProfile> profiles = wargear.profiles();
        parent.append(wrapTitle(wargear.title(), opts));
        int len = profiles.length();
        
        // profile
        if(len > 0)
        {
            HtmlNode table("table");
            table.append(
                HtmlNode("tr").append(
                    HtmlNode("th").append("&nbsp;", false)
                ).append(
                    HtmlNode("th", "Range")
                ).append(
                    HtmlNode("th", "Strength")
                ).append(
                    HtmlNode("th", "AP")
                ).append(
                    HtmlNode("th", "Type")
                ).append(
                    HtmlNode("th", "Page")
                )
            );
            for (int i = 0 ; i < len; i++)
            {
                QList<RuleRef*> rules = profiles[i].ruleRefs();
                qSort(rules.begin(), rules.end(), compareRulePtr);
                HtmlNode types("td");
                int rlen = rules.length();
                for(int j = 0; j < rlen; j++)
                {
                    append(types, *rules[j], InlineNode);
                    if((j+1) < rlen)
                        types.append(", ", true);
                }
                
                table.append(
                    HtmlNode("tr").append(
                        HtmlNode("td", profiles[i].name(), wargear.name())
                    ).append(
                        HtmlNode("td", profiles[i].range(), "-")
                    ).append(
                        HtmlNode("td", profiles[i].strength(), "-")
                    ).append(
                        HtmlNode("td", profiles[i].armourPenetration(), "-")
                    ).append(
                        types
                    )
                );
            }
            parent.append(table);
        }
        
        if(!wargear.description().isEmpty())
        {
            QString body = Qt::escape(wargear.description());
            //qDebug() << body;
            append(parent, body, children);
        }
        else if(!wargear.brief().isEmpty())
            parent.append(Qt::escape(wargear.brief()));
    }
}





void WarPage::append(HtmlNode& parent, QString& markup, NodeOptions opts)
{
    QStringList parts = markup.trimmed().split('\n', QString::KeepEmptyParts);
    int len = parts.length();
    HtmlNode block("p");
    MarkupLine previous = BreakLine, current;
    for(int i = 0; i < len; i++)
    {
        QString part = parts[i].simplified();
        if(part.isEmpty() && !block.isEmpty())
        {
            parent.append(block);
            block = HtmlNode("p");
            current = BreakLine;
        }
        else if(!part.isEmpty())
        {
            current = tags(part, opts);
            refs(part);
            if(current == HeaderLine)
            {
                if(!block.isEmpty())
                    parent.append(block);
                parent.append(part, false);
                block = HtmlNode("p");
            }
            else if(current == IndentedLine)
            {
                if(previous != IndentedLine)
                {
                    if(!block.isEmpty())
                        parent.append(block);
                    
                    block = HtmlNode("blockquote");
                }
                
                if(!block.isEmpty())
                    block.append(HtmlNode("br"));
                block.append(part, false);
            }
            else if(current == BreakLine)
            {
                if(previous == IndentedLine)
                {
                    if(!block.isEmpty())
                        parent.append(block);
                    block = HtmlNode("p");
                }
                
                if(!block.isEmpty())
                    block.append(HtmlNode("br"));
                block.append(part, false);
            }
        }
        previous = current;
    }
    
    if(!block.isEmpty())
        parent.append(block);
}

void WarPage::cutoff(QString& markup, const MarkupReference& ref, int len)
{
    int end;
    for(end = len; 
        end > 0 && !markup[end].isSpace();
        end--);
    
    end++;
    
    HtmlNode more("a");
    more.append("[more &rarr;]", false);
    more.href(ref);
    markup = markup.left(end) + more.toHtml();
}

void WarPage::refs(QString& markup)
{
    QRegExp re("\\[\\[\\s*(\\w+)\\s*\\|*([^\\|\\]]*)\\]\\]");
    int pos = 0;
    
    while((pos = re.indexIn(markup, pos)) >= 0)
    {
        MarkupReference r;
        r.prefix = NullPrefix;
        r.title = "";
        r.name = "";
        r.id = re.cap(1).trimmed();
        
        if(!re.cap(2).trimmed().isEmpty())
            r.name = re.cap(2).trimmed();
        
        HtmlNode refnode = resolveReference(r);
        QString replace = refnode.toHtml();
        markup.replace(pos, re.matchedLength(), replace);
        pos += replace.length();
    }
}

WarPage::MarkupLine WarPage::tags(QString& markup, WarPage::NodeOptions opts)
{
    if(markup.isEmpty())
        return BreakLine;
    
    MarkupLine ret = BreakLine;
    if(markup[0] == '#')
    {
        if(markup.length() < 2)
            return BreakLine;
        
        int level = opts.testFlag(EntityNode) ? 2 : 1;
        int count = beginingCount(markup, '#');
        
        QString htag = 'h' + QString::number(count + level);
        HtmlNode tag = HtmlNode(htag);
        tag.append(markup.remove(0, count).trimmed(), false);
        markup = tag.toHtml();
        
        return HeaderLine;
    }
    else if(markup.startsWith("&gt;"))
    {
        markup = markup.remove(0, 4).trimmed();
        ret = IndentedLine;
    }
    
    QRegExp re;
    re.setMinimal(true);
    
    re.setPattern("\\*\\*(.*)\\*\\*");
    markup.replace(re, "<b>\\1</b>");
    
    re.setPattern("__(.*)__");
    markup.replace(re, "<i>\\1</i>");
    
    markup.replace("--", "&mdash;");
    markup.replace(QRegExp("^\\*"), "&bull;");
    
    return ret;
}

int WarPage::beginingCount(const QString& txt, char c) const
{
    int len = txt.length(), ret = 0;
    for(int i = 0; i < len && txt[i] == c; i++)
        ret++;
    
    return ret;
}
