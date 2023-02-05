COMPILER = CC
DRIVER = TestEmployeeList
CLASS1 = Employee
CLASS2 = IndexList
\$(DRIVER) : \$(DRIVER).o \$(CLASS1).o \$(CLASS2).o
	\$(COMPILER) -o \$(DRIVER) \$(DRIVER).o \$(CLASS1).o \$(CLASS2).o
\$(DRIVER).o : \$(DRIVER).cpp \$(CLASS2).cpp \$(CLASS2).h \$(CLASS1).cpp \$(CLASS1).h
	\$(COMPILER) -c \$(DRIVER).cpp -o \$(DRIVER).o
\$(CLASS2).o : \$(CLASS2).cpp \$(CLASS2).h \$(CLASS1).cpp \$(CLASS1).h
	\$(COMPILER) -c \$(CLASS2).cpp -o \$(CLASS2).o
\$(CLASS1).o : \$(CLASS1).cpp \$(CLASS1).h
	\$(COMPILER) -c \$(CLASS1).cpp -o \$(CLASS1).o
clean:
	@ /bin/rm -f *.o
