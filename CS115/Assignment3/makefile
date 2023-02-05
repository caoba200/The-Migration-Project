COMPILER = CC
DRIVER = TestCalendar
FILE = Calendar
\$(DRIVER) : \$(DRIVER).o \$(FILE).o
	\$(COMPILER) -o \$(DRIVER) \$(DRIVER).o \$(FILE).o
\$(DRIVER).o : \$(DRIVER).cpp \$(FILE).cpp \$(FILE).h
	\$(COMPILER) -c \$(DRIVER).cpp -o \$(DRIVER).o
\$(FILE).o : \$(FILE).cpp \$(FILE).h
	\$(COMPILER) -c \$(FILE).cpp -o \$(FILE).o
clean:
	@ /bin/rm -f *.o
