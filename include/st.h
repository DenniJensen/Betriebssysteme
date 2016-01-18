#ifndef _ST_H_
#define _ST_H_

unsigned int calculate_steps(unsigned int msec);
void st_init(void); 
void st_set_interval(unsigned int msec); 
void st_handle_irq(void); 
 
#endif /* _ST_H_ */
