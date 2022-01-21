# distutils: language = c++
# distutils: sources = PyPtsim.cpp

from libcpp.string cimport string


cdef extern from "PyPtsim.h" :
	cdef cppclass PyPtsim_ :
		PyPtsim_()
		void setName(string)
		void setOption(string,string)
		int Initialize()
		void AddLog(int,int,int,string,string,int,int,int)
		int Performance()

cdef class PyPtsim :
	cdef PyPtsim_ *thisptr

	def __cinit__(self) :
		self.thisptr = new PyPtsim_()
	def __dealloc__(self) :
		del self.thisptr
	def setOption(self,key,param) :
		self.thisptr.setOption(key,param)
	def setName(self,str) :
		self.thisptr.setName(str)
	def Initialize(self) :
		return self.thisptr.Initialize()
	def AddLog(self,yy,mm,dd,code,name,pri,qua,order) :
		return self.thisptr.AddLog(yy,mm,dd,code,name,pri,qua,order)
	def Performance(self) :
		return self.thisptr.Performance()

