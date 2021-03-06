// $Id: inode.cpp,v 1.4 2014-04-09 17:04:58-07 - - $

#include <cassert>
#include <iostream>

using namespace std;

#include "debug.h"
#include "inode.h"

int inode::next_inode_nr {1};

inode::inode(inode_t init_type):
   inode_nr (next_inode_nr++), type (init_type)
{
   switch (type) {
      case DIR_INODE:
           contents.dirents = new directory();
           break;
      case FILE_INODE:
           contents.data = new wordvec();
           break;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

//
// copy ctor -
//    Make a copy of a given inode.  This should not be used in
//    your program if you can avoid it, since it is expensive.
//    Here, we can leverage operator=.
//
inode::inode (const inode& that) {
   *this = that;
}

//
// operator= -
//    Assignment operator.  Copy an inode.  Make a copy of a
//    given inode.  This should not be used in your program if
//    you can avoid it, since it is expensive.
//
inode& inode::operator= (const inode& that) {
   if (this != &that) {
      inode_nr = that.inode_nr;
      type = that.type;
      contents = that.contents;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
   return *this;
}


int inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}

int inode::size() const {
   int size {0};
   DEBUGF ('i', "size = " << size);
   return size;
}

const wordvec& inode::readfile() const {
   DEBUGF ('i', *contents.data);
   assert (type == FILE_INODE);
   return *contents.data;
}

void inode::writefile (const wordvec& words) {
   DEBUGF ('i', words);
   assert (type == FILE_INODE);
}

void inode::remove (const string& filename) {
   DEBUGF ('i', filename);
   assert (type == DIR_INODE);
}

inode_state::inode_state() {
   DEBUGF ('i', "root = " << (void*) root << ", cwd = " << (void*) cwd
          << ", prompt = " << prompt);
}

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

