CC = gcc
CXX = g++
RM = rm -f

all:
	$(CXX) exercise1-overloading.cpp -o exercise1-overloading
	$(CXX) exercise2-inheritance.cpp -o exercise2-inheritance
	$(CXX) exercise3-polymorphism.cpp -o exercise3-polymorphism
	$(CXX) exercise4-serialization.cpp -o exercise4-serialization
	$(CXX) exercise5-stl.cpp -o exercise5-stl
	$(CXX) final-project.cpp -o final-project

clean:
	$(RM) exercise1-overloading exercise2-inheritance
	$(RM) exercise3-polymorphism exercise4-serialization
	$(RM) exercise5-stl final-project
