void contar_RPM(void);
void set_Pwm(unsigned int num);
void delay(int tiempo);
void arrancar_motor_sin_control(void);
void arrancar_motor(void);
void apagar_motor(void);
void control_RPM(unsigned short rpm_real, unsigned short rpm_ideal);
void RPM_instantaneo(void);
void resetear_motor(void);
void configurar_motor(void);
void check_watchdog();
void refresh_watchDog();
void generar_onda_cuadrada(void);
