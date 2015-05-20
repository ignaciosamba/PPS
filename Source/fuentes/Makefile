TARGET=../test/test_exec
TEST_O= conversor_logic.o interfaz.o
# CONF_D= configurador.c configurador.h headers_logic.h conversor.h
CONV_D= conversor_logic.c conversor_logic.h headers_logic.h
INTF_D= interfaz.c interfaz.h headers_logic.h conversor_logic.h impresiones.
# TEST_CONF_O= ../test/test_configurador.o configurador.o
# TEST_CONF_D= ../test/test_configurador.c headers_logic.h ../test/minunit.h configurador.h
TEST_CONV_O= ../test/test_conversor.o conversor_logic.o
TEST_CONV_D= ../test/test_conversor.c headers_logic.h ../test/minunit.h conversor_logic.h
TEST_INTF_O= ../test/test_interfaz.o interfaz.o conversor_logic.o
TEST_INTF_D= ../test/test_interfaz.c headers_logic.h ../test/minunit.h interfaz.h conversor_logic.h

test: testconversor testinterfaz
	@echo TESTS_OK

#armando los archivos ppales

#../test/test_exec: $(TEST_O)
#	gcc -pg $(TEST_O) -o $(TARGET)

conversor_logic.o: $(CONV_D)
	gcc -pg -c conversor_logic.c -o conversor_logic.o

interfaz.o: $(INTF_D)
	gcc -pg -c interfaz.c -o interfaz.o


#armando los tests

#test configurador

# testconfigurador: ../test/test_configurador
# 	@echo test configurador iniciado
# 	@../test/test_configurador
# 	@echo tests de configurador pasaron

# ../test/test_configurador: $(TEST_CONF_O)
# 	gcc -pg $(TEST_CONF_O) -o ../test/test_configurador

# ../test/test_configurador.o: $(TEST_CONF_D)
# 	gcc -c ../test/test_configurador.c -o ../test/test_configurador.o


#test conversor

testconversor: ../test/test_conversor
	@echo test conversor iniciado
	@../test/test_conversor
	@echo tests de conversor pasaron

../test/test_conversor: $(TEST_CONV_O)
	gcc -pg $(TEST_CONV_O) -o ../test/test_conversor

../test/test_conversor.o: $(TEST_CONV_D)
	gcc -c ../test/test_conversor.c -o ../test/test_conversor.o


#test interfaz

testinterfaz: ../test/test_interfaz
	@echo test interfaz iniciado
	@../test/test_interfaz
	@echo tests de interfaz pasaron

../test/test_interfaz: $(TEST_INTF_O)
	gcc -pg $(TEST_INTF_O) -o ../test/test_interfaz

../test/test_interfaz.o: $(TEST_INTF_D)
	gcc -c ../test/test_interfaz.c -o ../test/test_interfaz.o

clean:
	rm *.o