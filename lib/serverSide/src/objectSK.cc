// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.

#include "object.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_2;



void
EntryIdl::operator>>= (cdrStream &_n) const
{
  _n.marshalString(first_name,0);
  _n.marshalString(last_name,0);
  _n.marshalString(father_name,0);
  _n.marshalString(phone,0);

}

void
EntryIdl::operator<<= (cdrStream &_n)
{
  first_name = _n.unmarshalString(0);
  last_name = _n.unmarshalString(0);
  father_name = _n.unmarshalString(0);
  phone = _n.unmarshalString(0);

}

void
MyInterface::Entries::operator>>= (cdrStream &_n) const
{
  (const _CORBA_Unbounded_Sequence< EntryIdl > &) m_entries >>= _n;

}

void
MyInterface::Entries::operator<<= (cdrStream &_n)
{
  (_CORBA_Unbounded_Sequence< EntryIdl > &)m_entries <<= _n;

}

MyInterface_ptr MyInterface_Helper::_nil() {
  return ::MyInterface::_nil();
}

::CORBA::Boolean MyInterface_Helper::is_nil(::MyInterface_ptr p) {
  return ::CORBA::is_nil(p);

}

void MyInterface_Helper::release(::MyInterface_ptr p) {
  ::CORBA::release(p);
}

void MyInterface_Helper::marshalObjRef(::MyInterface_ptr obj, cdrStream& s) {
  ::MyInterface::_marshalObjRef(obj, s);
}

MyInterface_ptr MyInterface_Helper::unmarshalObjRef(cdrStream& s) {
  return ::MyInterface::_unmarshalObjRef(s);
}

void MyInterface_Helper::duplicate(::MyInterface_ptr obj) {
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
}

MyInterface_ptr
MyInterface::_duplicate(::MyInterface_ptr obj)
{
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
  return obj;
}

MyInterface_ptr
MyInterface::_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


MyInterface_ptr
MyInterface::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

MyInterface_ptr
MyInterface::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_MyInterface _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_MyInterface* _the_nil_ptr = 0;
  if (!_the_nil_ptr) {
    omni::nilRefLock().lock();
    if (!_the_nil_ptr) {
      _the_nil_ptr = new _objref_MyInterface;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* MyInterface::_PD_repoId = "IDL:MyInterface:1.0";


_objref_MyInterface::~_objref_MyInterface() {
  
}


_objref_MyInterface::_objref_MyInterface(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::MyInterface::_PD_repoId, ior, id, 1)
   
   
{
  _PR_setobj(this);
}

void*
_objref_MyInterface::_ptrToObjRef(const char* id)
{
  if (id == ::MyInterface::_PD_repoId)
    return (::MyInterface_ptr) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (::CORBA::Object_ptr) this;

  if (omni::strMatch(id, ::MyInterface::_PD_repoId))
    return (::MyInterface_ptr) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (::CORBA::Object_ptr) this;

  return 0;
}


//
// Code for MyInterface::load

// Proxy call descriptor class. Mangled signature:
//  void_i_clong_o_cMyInterface_mEntries
class _0RL_cd_9d56a81675c47daa_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_9d56a81675c47daa_00000000(LocalCallFn lcfn, const char* op_, size_t oplen, _CORBA_Boolean upcall=0)
    : omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::Long arg_0;
  MyInterface::Entries_var arg_1;
};

void _0RL_cd_9d56a81675c47daa_00000000::marshalArguments(cdrStream& _n)
{
  arg_0 >>= _n;

}

void _0RL_cd_9d56a81675c47daa_00000000::unmarshalArguments(cdrStream& _n)
{
  (::CORBA::Long&)arg_0 <<= _n;

}

void _0RL_cd_9d56a81675c47daa_00000000::marshalReturnedValues(cdrStream& _n)
{
  (const MyInterface::Entries&) arg_1 >>= _n;

}

void _0RL_cd_9d56a81675c47daa_00000000::unmarshalReturnedValues(cdrStream& _n)
{
  arg_1 = new MyInterface::Entries;
  (MyInterface::Entries&)arg_1 <<= _n;

}

const char* const _0RL_cd_9d56a81675c47daa_00000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_9d56a81675c47daa_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_9d56a81675c47daa_00000000* tcd = (_0RL_cd_9d56a81675c47daa_00000000*)cd;
  _impl_MyInterface* impl = (_impl_MyInterface*) svnt->_ptrToInterface(MyInterface::_PD_repoId);
  impl->load(tcd->arg_0, tcd->arg_1.out());


}

void _objref_MyInterface::load(::CORBA::Long action, ::MyInterface::Entries_out ent)
{
  _0RL_cd_9d56a81675c47daa_00000000 _call_desc(_0RL_lcfn_9d56a81675c47daa_10000000, "load", 5);
  _call_desc.arg_0 = action;

  _invoke(_call_desc);
  ent = _call_desc.arg_1._retn();


}


//
// Code for MyInterface::changeRequest

// Proxy call descriptor class. Mangled signature:
//  void_i_clong_n_cMyInterface_mEntries
class _0RL_cd_9d56a81675c47daa_20000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_9d56a81675c47daa_20000000(LocalCallFn lcfn, const char* op_, size_t oplen, _CORBA_Boolean upcall=0)
    : omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  ::CORBA::Long arg_0;
  MyInterface::Entries_var arg_1_;
  MyInterface::Entries* arg_1;
};

void _0RL_cd_9d56a81675c47daa_20000000::marshalArguments(cdrStream& _n)
{
  arg_0 >>= _n;
  (const MyInterface::Entries&) *arg_1 >>= _n;

}

void _0RL_cd_9d56a81675c47daa_20000000::unmarshalArguments(cdrStream& _n)
{
  (::CORBA::Long&)arg_0 <<= _n;
  arg_1_ = new MyInterface::Entries;
  (MyInterface::Entries&)arg_1_ <<= _n;
  arg_1 = &arg_1_.inout();

}

void _0RL_cd_9d56a81675c47daa_20000000::marshalReturnedValues(cdrStream& _n)
{
  (const MyInterface::Entries&) *arg_1 >>= _n;

}

void _0RL_cd_9d56a81675c47daa_20000000::unmarshalReturnedValues(cdrStream& _n)
{
  (MyInterface::Entries&)*arg_1 <<= _n;

}

const char* const _0RL_cd_9d56a81675c47daa_20000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_9d56a81675c47daa_30000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_9d56a81675c47daa_20000000* tcd = (_0RL_cd_9d56a81675c47daa_20000000*)cd;
  _impl_MyInterface* impl = (_impl_MyInterface*) svnt->_ptrToInterface(MyInterface::_PD_repoId);
  impl->changeRequest(tcd->arg_0, *tcd->arg_1);


}

void _objref_MyInterface::changeRequest(::CORBA::Long action, ::MyInterface::Entries& entr)
{
  _0RL_cd_9d56a81675c47daa_20000000 _call_desc(_0RL_lcfn_9d56a81675c47daa_30000000, "changeRequest", 14);
  _call_desc.arg_0 = action;
  _call_desc.arg_1 = &(::MyInterface::Entries&) entr;

  _invoke(_call_desc);



}

_pof_MyInterface::~_pof_MyInterface() {}


omniObjRef*
_pof_MyInterface::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::_objref_MyInterface(ior, id);
}


::CORBA::Boolean
_pof_MyInterface::is_a(const char* id) const
{
  if (omni::ptrStrMatch(id, ::MyInterface::_PD_repoId))
    return 1;
  
  return 0;
}

const _pof_MyInterface _the_pof_MyInterface;

_impl_MyInterface::~_impl_MyInterface() {}


::CORBA::Boolean
_impl_MyInterface::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if (omni::strMatch(op, "load")) {

    _0RL_cd_9d56a81675c47daa_00000000 _call_desc(_0RL_lcfn_9d56a81675c47daa_10000000, "load", 5, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if (omni::strMatch(op, "changeRequest")) {

    _0RL_cd_9d56a81675c47daa_20000000 _call_desc(_0RL_lcfn_9d56a81675c47daa_30000000, "changeRequest", 14, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
_impl_MyInterface::_ptrToInterface(const char* id)
{
  if (id == ::MyInterface::_PD_repoId)
    return (::_impl_MyInterface*) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (void*) 1;

  if (omni::strMatch(id, ::MyInterface::_PD_repoId))
    return (::_impl_MyInterface*) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (void*) 1;
  return 0;
}

const char*
_impl_MyInterface::_mostDerivedRepoId()
{
  return ::MyInterface::_PD_repoId;
}

POA_MyInterface::~POA_MyInterface() {}

