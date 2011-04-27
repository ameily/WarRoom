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


#include "Wargear.h"
#include "Race.h"
#include "TextFormatter.h"

Wargear::Wargear(const Race& race) : m_profiles(), m_brief(), m_description(),
    m_name(), m_id()
{
    m_race = &race;
}

/*Wargear::Wargear(const Wargear& other) : m_profiles(other.m_profiles),
    m_brief(other.m_brief), m_description(other.m_description),
    m_name(other.m_name), m_id(other.m_id)
{

}*/

Wargear::Wargear() : m_profiles(), m_brief(), m_description(), m_name(), m_id()
{
    m_race = NULL;
}


Wargear::Wargear(const Wargear& other) : //m_profiles(other.m_profiles),
    m_brief(other.m_brief), m_description(other.m_description), m_id(other.m_id),
    m_name(other.m_name)
{
    m_race = other.m_race;
    
    // reset profiles to set part to this
    int len = other.m_profiles.length();
    for(int i = 0; i < len; i++)
    {
        WargearProfile p(other.m_profiles[i], this);
        m_profiles.append(p);
    }
}

Wargear::Wargear(const QDomElement& ele, const Race& race)
    throw(XmlParseException) : m_profiles(), m_brief(), m_description(),
    m_name(), m_id()
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    TextFormatter& formatter = TextFormatter::instance();
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "brief")
                m_brief = current.text().simplified();
            else if(current.nodeName() == "description")
                m_description = formatter.fromXml(current);
            else if(current.nodeName() == "name")
                m_name = current.text().simplified();
            else if(current.nodeName() == "id")
                m_id = current.text().simplified();
            else if(current.nodeName() == "profiles")
                profilesFromXml(current);
            else
                throw XmlParseException("invalid wargear node", current);
        }
    }
    
    if(m_id.isEmpty())
        throw XmlParseException("missing wargear id node", ele);
    
    if(m_name.isEmpty())
        throw XmlParseException("missing wargear name node", ele);
    
    len = m_profiles.length();
    for(int i = 0; i < len; i++)
    {
        if(m_profiles[i].name().isEmpty())
            m_profiles[i].name(m_name);
    }
    
    m_race = &race;
}

void Wargear::profilesFromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        
        if(!current.isNull())
        {
            if(current.nodeName() == "profile")
                m_profiles.append(WargearProfile(current, *this));
            else
            {
                throw XmlParseException("invalid wargear profile list node",
                                        current);
            }
        }
    }
}


Wargear::~Wargear()
{
    /*
    QMutableListIterator<WargearProfile*> i(m_profiles);
    WargearProfile *dead;
    while(i.hasNext())
    {
        dead = i.next();
        i.remove();
        delete dead;
    }
    */
}


Wargear& Wargear::operator=(const Wargear& other)
{
    if(*this == other)
        return *this;
    
    m_brief = other.m_brief;
    m_description = other.m_description;
    m_name = other.m_name;
    m_id = other.m_id;
    m_race = other.m_race;
    
    m_profiles.clear();
    
    // reset profiles to set part to this
    int len = other.m_profiles.length();
    for(int i = 0; i < len; i++)
    {
        WargearProfile p(other.m_profiles[i], this);
        m_profiles.append(p);
    }
    
    return *this;
}


bool Wargear::operator==(const Wargear& other) const
{
    return m_brief == other.m_brief && m_description == other.m_description &&
        m_profiles == other.m_profiles && m_name == other.m_name &&
        other.m_id == other.m_id && m_race == other.m_race;
}

const QString& Wargear::brief() const
{
    return m_brief;
}

void Wargear::brief(const QString& brf)
{
    m_brief = brf;
}

const QString& Wargear::description() const
{
    return m_description;
}

void Wargear::description(const QString& desc)
{
    m_description = desc;
}

void Wargear::id(const QString& wid)
{
    m_id = wid;
}

const QString& Wargear::id() const
{
    return m_id;
}

void Wargear::name(const QString& nm)
{
    m_name = nm;
}

const QString& Wargear::name() const
{
    return m_name;
}

const Race& Wargear::race() const
{
    return *m_race;
}



QList<WargearProfile*> Wargear::profiles()
{
    QList<WargearProfile*> ret;
    int len = m_profiles.length();
    
    for(int i = 0; i < len; i++)
        ret.append(&m_profiles[i]);
    
    return ret;
}

QList<WargearProfile> Wargear::profiles() const
{
    return m_profiles;
}

bool Wargear::removeProfile(const WargearProfile& profile)
{
    int i = m_profiles.indexOf(profile);
    if(i >= 0)
        m_profiles.removeAt(i);
    
    return i >= 0;
}

WargearProfile* Wargear::addProfile(const WargearProfile& profile)
{
    if(m_profiles.contains(profile))
        return 0;
    
    m_profiles.append(profile);
    return &m_profiles.last();
}

QDomElement& Wargear::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    if(m_id.isEmpty())
        throw ValidationException("Wargear", "id", "is null");
    
    if(m_name.isEmpty())
        throw ValidationException("Wargear", "name", "is null");
    
    appendElement(doc, parent, "id", m_id);
    appendElement(doc, parent, "name", m_name);
    appendElement(doc, parent, "brief", m_brief);
    
    if(!m_description.isEmpty())
        appendElement(doc, parent, "description", m_description);
    
    if(m_profiles.length() > 0)
    {
        QDomElement profiles = doc.createElement("profiles");
        QDomElement ele;
        int len = m_profiles.length();
        for(int i = 0; i < len; i++)
        {
            ele = doc.createElement("profile");
            m_profiles[i].toXml(doc, ele);
            profiles.appendChild(ele);
        }
    }
    
    return parent;
}

bool Wargear::isReference() const
{
    return false;
}

void Wargear::resolveReferences() throw(UnresolvedReferenceException)
{
    int len = m_profiles.length();
    for(int i = 0; i < len; i++)
        m_profiles[i].resolveReferences();
}

bool Wargear::isNull() const
{
    return m_race == NULL;
}

Wargear Wargear::Null()
{
    return Wargear();
}



