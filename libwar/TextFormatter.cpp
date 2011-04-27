/*
    This file is part of the War Library (libwar)
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


#include "TextFormatter.h"
#include <QRegExp>
#include <QUrl>

TextFormatter* TextFormatter::m_instance = 0;

void TextFormatter::destroy()
{
    if(m_instance)
        delete m_instance;
    
    m_instance = NULL;
}

TextFormatter::TextFormatter()
{
}

TextFormatter& TextFormatter::instance()
{
    if(!m_instance)
        m_instance = new TextFormatter();
    
    return *m_instance;
}

QString TextFormatter::fromXml(const QDomElement& ele) const
{
    QString ret = ele.text().simplified();
    ret.replace("[lb]", "[lb]\n");
    ret.replace("[p]", "\n[p]\n");
    ret.replace("\n ", "\n");
    
    return ret;
}

QString TextFormatter::toHtml(const QString& in, Game& game) const
{
    QString ret = in;
    toHtml(ret);
    parseRefs(ret, &game, 0);
    
    return ret;
}

QString TextFormatter::toHtml(const QString& in, Race& race) const
{
    QString ret = in;
    toHtml(ret);
    parseRefs(ret, 0, &race);
    
    return ret;
}

void TextFormatter::toHtml(QString& out) const
{
    out.replace("[lb]", "<br/>");
    out.replace("[p]", "<br/><br/>");
    
    out.replace("[b]", "<b>");
    out.replace("[/b]", "</b>");
    
    out.replace("[i]", "<i>");
    out.replace("[/i]", "</i>");
    
    out.replace("[u]", "<u>");
    out.replace("[/u]", "</u>");
}


void TextFormatter::parseRefs(QString& in, Game* game, Race* race) const
{
    QRegExp re("\\[\\[\\s*(\\S+)\\s*\\]\\]");
    int pos = 0;
    
    while((pos = re.indexIn(in, pos)) >= 0)
    {
        ReferenceString r;
        r.id = re.cap(1);
        r.name = "";
        r.prefix = "";
        r.title = "";
        
        QString replace = resolveRef(r, game, race);
        in.replace(pos, re.matchedLength(), replace);
        pos += replace.length() - re.matchedLength();
    }
    
    re = QRegExp("\\[\\[\\s*(\\S+)\\s*\\|\\s*(\\S.+\\S)\\s*\\]\\]");
    pos = 0;
    while((pos = re.indexIn(in, pos)) >= 0)
    {
        ReferenceString r;
        r.id = re.cap(1);
        r.name = re.cap(2);
        r.prefix = "";
        r.title = "";
        
        QString replace = resolveRef(r, game, race);
        in.replace(pos, re.matchedLength(), replace);
        pos += replace.length() - re.matchedLength();
    }
}

QString TextFormatter::resolveRef(ReferenceString& ref, Game* game, Race* race) const
{
    QString ret;
    if(game)
    {
        Rule *r = game->getRule(ref.id);
        if(r)
        {
            ref.prefix = "rule";
            ref.name = r->name();
            ref.title = r->brief();
        }
    }
    else
    {
        const Rule *r = race->resolveRuleReference(ref.id);
        Wargear *w = race->getWargear(ref.id);
        Unit *u = race->getUnit(ref.id);
        
        if(r)
        {
            ref.prefix = "rule";
            ref.title = r->brief();
        }
        else if(w)
            ref.prefix = "wargear";
        else if(u)
            ref.prefix = "unit";
    }
    
    if(!ref.prefix.isEmpty())
    {
        QUrl url(ref.prefix + "://" + ref.id + "?name=" + ref.name);
        ret = "<a href=\"" + url.toString() + "\" ";
        if(!ref.title.isEmpty())
            ret += "title=\"" + ref.title + "\" ";
        
        ret += ">" + ref.name + "</a>";
    }
    else
    {
        ret = "<span style='color:#ff0000;text-decoration:underline'>";
        if(ref.name.isEmpty())
            ret += ref.id;
        else
            ret += ref.name;
        
        ret += "</span>";
    }
    
    return ret;
}





