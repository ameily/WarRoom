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


#include "WargearList.h"
#include "Race.h"
//#include <QtAlgorithms>

WargearList::WargearList() : m_wargears(), m_unresolvedWargears()
{

}

WargearList::WargearList(const WargearList& other) :
    m_wargears(other.m_wargears),
    m_unresolvedWargears(other.m_unresolvedWargears)
{

}

WargearList::~WargearList()
{
    /*
    QMutableHashIterator<QString, IWargear> i(m_wargears);
    IWargear* dead;
    while(i.hasNext())
    {
        i.next();
        dead = i.value();
        i.remove();
        delete dead;
    }
    */
}


WargearList& WargearList::operator=(const WargearList& other)
{
    if(*this == other)
        return *this;
    
    m_wargears = other.m_wargears;
    m_unresolvedWargears = other.m_unresolvedWargears;
    return *this;
}


/*
void WargearList::addWargear(const IWargear& wargear)
{
    if(m_wargears.contains(wargear.id()))
        *(m_wargears[wargear.id()]) = wargear;
    else
        m_wargears.insert(wargear.id(), new WargearRef(wargear));
}
*/
Wargear* WargearList::addWargear(const Wargear& wargear)
{
    if(hasWargear(wargear.id()))
        return 0;
    
    m_wargears.insert(wargear.id(), wargear);
    return getWargear(wargear.id());
}

bool WargearList::hasWargear(const QString& id) const
{
    return m_wargears.contains(id);
}



QList<Wargear> WargearList::findWargearsByName(const QString& name) const
{
    QList<Wargear> ret;
    QHashIterator<QString, Wargear> i(m_wargears);
    
    while(i.hasNext())
    {
        i.next();
        if(i.value().name().contains(name))
            ret.append(i.value());
    }
    
    return ret;
}

Wargear WargearList::getWargear(const QString& id) const
{
    if(m_wargears.contains(id))
        return m_wargears[id];
    
    return Wargear::Null();
}

Wargear* WargearList::getWargear(const QString& id)
{
    Wargear *ret = NULL;
    if(m_wargears.contains(id))
        ret = &m_wargears[id];
    
    return ret;
}

Wargear* WargearList::resetWargearId(const QString& oldId, const QString& newId)
{
    if(hasWargear(oldId) || hasWargear(newId))
        return 0;
    
    Wargear wargear = m_wargears.take(oldId);
    wargear.id(newId);
    return addWargear(wargear);
}


bool WargearList::operator==(const WargearList& other) const
{
    return m_wargears == other.m_wargears &&
        m_unresolvedWargears == other.m_unresolvedWargears;
}

bool WargearList::removeWargear(const Wargear& wargear)
{
    bool ret = true;
    if(m_wargears.contains(wargear.id()))
        m_wargears.remove(wargear.id());
    else
        ret = false;
    
    return ret;
}

QList<Wargear> WargearList::wargears() const
{
    return m_wargears.values();
}

QList< Wargear* > WargearList::wargears()
{
    QList<Wargear*> ret;
    QMutableHashIterator<QString, Wargear> i(m_wargears);
    while(i.hasNext())
    {
        i.next();
        ret.append(&i.value());
    }
    
    return ret;
}


void WargearList::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "wargear")
            {
                Wargear wg(current, race());
                m_wargears.insert(wg.id(), wg);
            }
            else
                throw XmlParseException("invalid wargear list node", current);
        }
    }
}

QDomElement& WargearList::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    QDomElement ele;
    QHashIterator<QString, Wargear> i(m_wargears);
    while(i.hasNext())
    {
        i.next();
        ele = doc.createElement("wargear");
        i.value().toXml(doc, ele);
        parent.appendChild(ele);
    }
    
    return parent;
}

void WargearList::resolveReferences() throw(UnresolvedReferenceException)
{
    QMutableHashIterator<QString, Wargear> i(m_wargears);
    while(i.hasNext())
    {
        i.next();
        i.value().resolveReferences();
    }
}


