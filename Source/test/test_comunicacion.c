#include "minunit.h"

 int tests_run = 0; 
 int res;

 static char * test_escuchar() 
{ 
	res = funcion_1();
    mu_assert("error, funcion_1 no respondio 10",res == 10);
    return 0;
}
 
 
 static char * all_tests() {
    mu_run_test(test_1);
     return 0;

 }
 
 int main(int argc, char **argv) {

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
          printf("TEST PASSED\n");
     } 
     return result != 0;
 }