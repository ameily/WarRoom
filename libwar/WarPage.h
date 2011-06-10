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


#ifndef WARPAGE_H
#define WARPAGE_H
#include <QString>
#include "Rule.h"
#include "RuleList.h"
#include "Game.h"
#include "Race.h"
#include <qmap.h>

class WarPage
{
public:
    enum RaceMode
    {
        UnitListMode,
        RuleListMode,
        WargearListMode
    };
    
    enum NodeOption
    {
        PageNode = 1,
        EntityNode = 2,
        InlineNode = 4,
        BriefDescription = 8,
        FullDescription = 16
    };
    Q_DECLARE_FLAGS(NodeOptions, NodeOption);
    
    
    enum ReferencePrefix
    {
        NullPrefix,
        RulePrefix,
        UnitPrefix,
        WargearPrefix
    };
    
    struct MarkupReference
    {
        ReferencePrefix prefix;
        QString name;
        QString id;
        QString title;
    };
    
    class HtmlNode
    {
    public:
        HtmlNode(const QString& tag, const QString& body = QString());
        HtmlNode(const HtmlNode& other);
        HtmlNode(const WarPage::MarkupReference& ref,
                 const QString& name = QString());
        HtmlNode();
        
        HtmlNode& operator=(const HtmlNode& other);
        HtmlNode& id(const QString& id);
        HtmlNode& colspan(const QString& span);
        HtmlNode& rowspan(const QString& span);
        HtmlNode& href(const QString& href);
        HtmlNode& href(const WarPage::MarkupReference& ref);
        HtmlNode& style(const QString& style);
        HtmlNode& title(const QString& title);
        HtmlNode& attr(const QString& atr, const QString& val);
        HtmlNode& append(const HtmlNode& tag);
        HtmlNode& append(const QString& txt, bool escape);
        HtmlNode& clear();
        bool isEmpty() const;
        static QString toString(ReferencePrefix prefix);
        
        QString toHtml() const;
        
    private:
        QString m_body;
        QString m_tag;
        QMap<QString, QString> m_attributes;
    };
    
    WarPage(Game& game);
    WarPage(Race& race, RaceMode mode);
    WarPage(const IRule& rule, RuleList& list, Race *race);
    WarPage(const WarPage& other);
    virtual WarPage& operator=(const WarPage& other);
    
    Race* race();
    RuleList* ruleList();
    const QString& id() const;
    const QString& name() const;
    
    QString toHtml() const;
    static QString markupFromXml(const QDomElement& ele);
    QString defaultStyleSheet() const;
    int maxDescriptionLength() const;
    
private:
    //HtmlNode convertToHtmlNode(const IRule& rule, WarPage::NodeOptions level);
    void initPage(const QString& title);
    //void cutOff(NodeLevel level, ReferencePrefix prefix, const QString& id, const QString& name,
    //            QString& out);
    
    void append(HtmlNode& parent, const IRule& rule, NodeOptions opts);
    void append(HtmlNode& parent, const Unit& unit, NodeOptions opts);
    void append(HtmlNode& parent, QString& markup, NodeOptions opts);
    void append(HtmlNode& parent, const UnitProfile& profile);
    bool tags(QString& markup, WarPage::NodeOptions opts);
    void refs(QString& markup);
    void cutoff(QString& markup, const WarPage::MarkupReference& ref, int len);
    
    MarkupReference toRef(const IRule& rule);
    
    HtmlNode wrapTitle(const QString& title, NodeOptions opts) const;
    NodeOptions childOptions(NodeOptions opts);
    //void convertToHtml(QString& out, HtmlNode& parent);
    //void convertReferences(QString& out);
    HtmlNode resolveReference(MarkupReference& ref);
    
    HtmlNode m_root;
    QString m_name;
    RuleList *m_rules;
    Race *m_race;
    QString m_id;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(WarPage::NodeOptions);

#endif // WARPAGE_H
