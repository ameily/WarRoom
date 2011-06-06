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


#include "Unit.h"
#include "Race.h"
#include <QDebug>


Unit::Unit() : WargearRefList(), RuleRefList(), m_profile(), m_id(), m_name(),
    m_page()
{
    m_race = NULL;
}

bool Unit::isNull() const
{
    return m_race == NULL;
}


Unit::Unit(const Race& race) : WargearRefList(), RuleRefList(), m_profile(),
    m_id(), m_name(), m_page()
{
    m_race = &race;
}

Unit::Unit(const Unit& other) : WargearRefList(other), RuleRefList(other),
    m_profile(other.m_profile), m_id(other.m_id), m_name(other.m_name),
    m_page(other.m_page)
{
    m_race = other.m_race;
}

Unit::Unit(const QDomElement& ele, const Race& race) : m_profile(), m_id(),
    m_name(), RuleRefList(), WargearRefList()
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "id")
                m_id = current.text().simplified();
            else if(current.nodeName() == "name")
                m_name = current.text().simplified();
            else if(current.nodeName() == "page")
                m_page = current.text().simplified();
            else if(current.nodeName() == "profile")
                m_profile = UnitProfile(current);
            else if(current.nodeName() == "rules")
                RuleRefList::fromXml(current);
            else if(current.nodeName() == "wargears")
                WargearRefList::fromXml(current);
            else
                throw XmlParseException("invalid unit node", current);
        }
    }
    
    if(m_id.isEmpty())
        throw XmlParseException("missing unit id node", ele);
    
    if(m_name.isEmpty())
        throw XmlParseException("missing unit name node", ele);
    
    if(m_page.isEmpty())
        throw XmlParseException("missing unit page node", ele);
    
    //if(m_profile.isNull())
    //    throw XmlParseException("missing unit profile node", ele);
    
    m_race = &race;
}


Unit::~Unit()
{

}

Unit& Unit::operator=(const Unit& other)
{
    if(*this == other)
        return *this;
    
    WargearRefList::operator=(other);
    RuleRefList::operator=(other);
    
    m_profile = other.m_profile;
    m_name = other.m_name;
    m_id = other.m_id;
    m_race = other.m_race;
    m_page = other.m_page;
    
    return *this;
}

bool Unit::operator==(const Unit& other) const
{
    return m_profile == other.m_profile && RuleRefList::operator==(other) &&
        WargearRefList::operator==(other) && m_id == other.m_id &&
        m_name == other.m_name && m_race == other.m_race &&
        m_page == other.m_page;
}

/*
void Unit::addProfile(const UnitProfile& profile)
{
    m_profiles.append(profile);
}

void Unit::removeProfile(const UnitProfile& profile)
{
    int i = m_profiles.indexOf(profile);
    if(i >= 0)
        m_profiles.removeAt(i);
}

const QList< UnitProfile > Unit::profiles() const
{
    return m_profiles;
}

QList< UnitProfile* > Unit::profiles()
{
    QList<UnitProfile*> ret;
    int len = m_profiles.length();
    
    for(int i = 0; i < len; i++)
        ret.append(&m_profiles[i]);
    
    return ret;
}
*/

const UnitProfile& Unit::profile() const
{
    return m_profile;
}

void Unit::profile(const UnitProfile& pf)
{
    m_profile = pf;
}

UnitProfile& Unit::profile()
{
    return m_profile;
}


const QString& Unit::id() const
{
    return m_id;
}

void Unit::id(const QString& uid)
{
    m_id = uid;
}

const QString& Unit::name() const
{
    return m_name;
}

void Unit::name(const QString& nm)
{
    m_name = nm;
}

const QString& Unit::page() const
{
    return m_page;
}

void Unit::page(const QString& upg)
{
    m_page = upg;
}


const Race& Unit::race() const
{
    return *m_race;
}


QDomElement& Unit::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    if(m_id.isEmpty())
        throw ValidationException("Unit", "id", "is null");
    
    if(m_name.isEmpty())
        throw ValidationException("Unit [" + m_id + "]", "name", "is null");
    
    if(m_page.isEmpty())
        throw ValidationException("Unit [" + m_id + "]", "page", "is null");
    
    //if(m_profile.isNull())
    //    throw ValidationException("Unit", "profile", "is null");
    
    QDomElement profileNode = doc.createElement("profile");
    m_profile.toXml(doc, profileNode);
    
    QDomElement wargearsNode = doc.createElement("wargears");
    WargearRefList::toXml(doc, wargearsNode);
    
    QDomElement rulesNode = doc.createElement("rules");
    RuleRefList::toXml(doc, rulesNode);
    
    appendElement(doc, parent, "id", m_id);
    appendElement(doc, parent, "name", m_name);
    appendElement(doc, parent, "page", m_page);
    
    parent.appendChild(profileNode);
    parent.appendChild(wargearsNode);
    parent.appendChild(rulesNode);
    
    return parent;
}

void Unit::resolveReferences() throw(UnresolvedReferenceException)
{
    WargearRefList::resolveReferences();
    RuleRefList::resolveReferences();
}

bool compareUnit(Unit*const& u1, Unit*const& u2)
{
    return QString::localeAwareCompare(u1->name().toLower(),
                                       u2->name().toLower()) < 0;
}
