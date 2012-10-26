#include "../../include/JSONHandler/ALRPCObjects/AddSubMenu_request.h"
#include "AddSubMenu_requestMarshaller.h"
#include "../../include/JSONHandler/ALRPCObjects/Marshaller.h"

#define PROTOCOL_VERSION	1


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Fri Oct 26 06:31:48 2012
  source stamp	Thu Oct 25 06:49:27 2012
  author	robok0der
*/

AddSubMenu_request& AddSubMenu_request::operator =(const AddSubMenu_request& c)
{
  menuID= c.menuID;
  position= c.position ? new unsigned int(c.position[0]) : 0;
  menuName= c.menuName;

  return *this;}


AddSubMenu_request::~AddSubMenu_request(void)
{
  if(position)
    delete position;
}


AddSubMenu_request::AddSubMenu_request(const AddSubMenu_request& c)
{
  *this=c;
}


bool AddSubMenu_request::checkIntegrity(void)
{
  return AddSubMenu_requestMarshaller::checkIntegrity(*this);
}


AddSubMenu_request::AddSubMenu_request(void) : ALRPCRequest(PROTOCOL_VERSION,Marshaller::METHOD_ADDSUBMENU_REQUEST),
      position(0)
{
}



bool AddSubMenu_request::set_menuID(unsigned int menuID_)
{
  if(menuID_>2000000000)  return false;
  menuID=menuID_;
  return true;
}

bool AddSubMenu_request::set_position(unsigned int position_)
{
  if(position_>1000)  return false;
  delete position;
  position=0;

  position=new unsigned int(position_);
  return true;
}

void AddSubMenu_request::reset_position(void)
{
  if(position)
    delete position;
  position=0;
}

bool AddSubMenu_request::set_menuName(const std::string& menuName_)
{
  if(menuName_.length()>500)  return false;
  menuName=menuName_;
  return true;
}




unsigned int AddSubMenu_request::get_menuID(void) const
{
  return menuID;
}

const unsigned int* AddSubMenu_request::get_position(void) const 
{
  return position;
}

const std::string& AddSubMenu_request::get_menuName(void) const 
{
  return menuName;
}

