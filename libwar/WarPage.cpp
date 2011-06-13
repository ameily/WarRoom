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

WarPage::WarPage(Race& race, RaceMode mode) : m_id(race.id()), m_root(),
    m_name(race.name())
{
    m_rules = &race;
    m_race = &race;
    HtmlNode body("body");
    QString subtitle;
    int len;
    
    if(mode == RuleListMode)
    {
        
    }
    else if(mode == WargearListMode)
    {
    }
    else // Unit List
    {
        subtitle = "Unit List";
        QList<Unit*> units = m_race->units();
        qSort(units.begin(), units.end(), compareUnit);
        len = units.length();
        
        for(int i = 0; i < len; i++)
            append(body, *units[i], EntityNode | BriefDescription);
    }
    
    initPage(race.name() + " -- " + subtitle);
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
    QList<WargearRef> wargears = unit.wargearRefs();
    QList<RuleRef> rules = unit.ruleRefs();
    qSort(wargears.begin(), wargears.end(), compateWargearRef);
    qSort(rules.begin(), rules.end(), compareRuleRef);
    
    NodeOptions childopts = childOptions(opts);
    append(parent, unit.profile());
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
                    tr.append(HtmlNode("td").append("&nbsp;", false));
                else if(col == unitCount)
                {
                    tr.append(
                        HtmlNode("td").colspan(QString::number(vehicleCount)).append(
                            HtmlNode("b", "ARMOUR")
                        )
                    );
                }
            }
            else if(row == 1)
                tr.append(HtmlNode("td").append(HtmlNode("b", current.key)));
            else if(row == 2)
                tr.append(HtmlNode("td", current.value));
        }
        table.append(tr);
    }
    
    parent.append(table);
}

/*
 * status = tags(part)
 * if status == header
 *     begin new paragraph (p)
 *     body.append(part)
 * else if status == indent
 *     if previous == indent
 *         paragraph.append(part)
 *     else
 *         begin new paragraph (div)
 *         paragraph.append(part)
 * else if status == inline
 *     if previous == indent
 *         begin new paragraph (p)
 *     paragraph.append(part)
 * 
 * begin(HtmlNode parent)
 *     if !parent.isEmpty()
 */
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
