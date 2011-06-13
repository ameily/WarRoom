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

WarPage::HtmlNode::HtmlNode(const QString& tag, const QString& body) : m_body(),
    m_tag(tag)
{
    m_body = Qt::escape(body);
}

WarPage::HtmlNode::HtmlNode(const WarPage::HtmlNode& other) : 
    m_body(other.m_body), m_tag(other.m_tag), m_attributes(other.m_attributes)
{

}

WarPage::HtmlNode::HtmlNode(const WarPage::MarkupReference& ref,
    const QString& name) : m_body(), m_tag(), m_attributes()
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
        style("color: #ff0000;");
    }
    else
    {
        m_tag = "a";
        href(toString(ref.prefix) + "://" + ref.id + "?name=" + finalName);
    }
    
    append(finalName, true);
    
    if(!ref.title.isEmpty())
        title(ref.title);
}


WarPage::HtmlNode::HtmlNode() : m_body(), m_tag(), m_attributes()
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

WarPage::HtmlNode& WarPage::HtmlNode::href(const WarPage::MarkupReference& ref)
{
    href(toString(ref.prefix) + "://" + ref.id + "?name=" + ref.name);
}



WarPage::HtmlNode& WarPage::HtmlNode::operator=(const WarPage::HtmlNode& other)
{
    m_body = other.m_body;
    m_attributes = other.m_attributes;
    m_tag = other.m_tag;
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
    m_attributes["href"] = QUrl(href).toEncoded();
    return *this;
}

WarPage::HtmlNode& WarPage::HtmlNode::id(const QString& id)
{
    return attr("id", id);
}

WarPage::HtmlNode& WarPage::HtmlNode::style(const QString& style)
{
    return attr("style", style);
}

WarPage::HtmlNode& WarPage::HtmlNode::title(const QString& title)
{
    return attr("title", title);
}

WarPage::HtmlNode& WarPage::HtmlNode::colspan(const QString& span)
{
    return attr("colspan", span);
}

WarPage::HtmlNode& WarPage::HtmlNode::rowspan(const QString& span)
{
    return attr("rowspan", span);
}

WarPage::HtmlNode& WarPage::HtmlNode::attr(const QString& key, const QString& val)
{
    m_attributes[key] = Qt::escape(val).replace("\"", "&quot;");
    return *this;
}


QString WarPage::HtmlNode::toHtml() const
{
    QString node = "<" + m_tag;
    
    QMapIterator<QString, QString> i(m_attributes);
    while(i.hasNext())
    {
        i.next();
        node += " " + i.key() + "=\"" + i.value() + "\"";
    }
    
    if(m_body.isEmpty())
        node += " />";
    else
        node += ">" + m_body + "</" + m_tag + ">";
    
    return node;
}

WarPage::HtmlNode& WarPage::HtmlNode::clear()
{
    m_body.clear();
}

bool WarPage::HtmlNode::isEmpty() const
{
    return m_body.isEmpty();
}
