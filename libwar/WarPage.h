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


#ifndef WARPAGE_H
#define WARPAGE_H
#include <QString>
#include "Rule.h"
#include "RuleList.h"
#include "Game.h"
#include "Race.h"

class WarPage
{
public:
    class HtmlNode
    {
    public:
        HtmlNode(const QString& tag, const QString& body = QString());
        HtmlNode(const HtmlNode& other);
        HtmlNode();
        
        HtmlNode& operator=(const HtmlNode& other);
        HtmlNode& id(const QString& id);
        HtmlNode& href(const QString& href);
        HtmlNode& style(const QString& style);
        HtmlNode& title(const QString& title);
        HtmlNode& append(const HtmlNode& tag);
        HtmlNode& append(const QString& txt, bool escape);
        
        QString toHtml() const;
        
    private:
        QString m_body;
        QString m_tag;
        QString m_id;
        QString m_href;
        QString m_style;
        QString m_title;
    };
    
    struct ReferenceString
    {
        QString prefix;
        QString name;
        QString id;
        QString title;
    };
    
    enum NodeLevel
    {
        Page,
        Section,
        SubSection,
        Inline
    };
    
    WarPage(Game& game);
    WarPage(const IRule& rule, RuleList& list, Race *race);
    /*WarPage(Race& race);
    WarPage(Unit& unit);
    WarPage(Wargear& wargear);*/
    
    Race* race();
    RuleList* ruleList();
    const QString& id() const;
    const QString& name() const;
    
    QString toHtml() const;
    static QString wrapWhiteSpaceTags(const QDomElement& ele);
    
private:
    HtmlNode convertToHtmlNode(const IRule& rule, int level);
    void initPage(const QString& title);
    HtmlNode wrapTitle(const QString& title, int level) const;
    void convertToHtml(QString& out);
    void convertReferences(QString& out);
    HtmlNode resolveReference(ReferenceString& ref);
    
    HtmlNode m_root;
    QString m_name;
    RuleList *m_rules;
    Race *m_race;
    QString m_id;
};

#endif // WARPAGE_H
