/*
 * ws2812_test.cpp
 *
 * Created: 25-Apr-24 12:00:39 AM
 * Author : Sadeed
 */ 

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
 #include <avr/interrupt.h>




	


int main(void) 
{

    DDRC = 0xff;
	DDRA = 0xff;
	
	
	TCCR1B |= 1<<CS12 | 1<<CS10 | 1<<WGM12;
//	TIMSK1 |= 1<<OCIE1A;
//	OCR1A = 19531;
//sei();
	
	
//	int LED_NUMC = 0;
	
	unsigned int Leds = 20; // no. of leds, minnimum is 1
	uint16_t LED_NUM = Leds*24  ;
	
	
			uint16_t n = 0;
		char Color_Flag = 1;
	int V = 0;
	
		uint16_t m1 = 0;
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Set Color Here	
volatile uint8_t R = 0x01;
volatile uint8_t G = 0x01;
volatile uint8_t B = 0x01;
	
volatile uint8_t R_Buff = 0;
		unsigned int R_Val = 0;
	 
	
volatile uint8_t G_Buff = 0;
		unsigned int G_Val = 0;
	
	
volatile uint8_t B_Buff = 0;
	unsigned int B_Val = 0;
	
	char Code = 0; 
	
volatile uint16_t array[1000]; // if you see any garbage values, you can make it static to make all elements 0, maybe 
	 
	//////////////////////////////////////////////// inverted because ws2812 starts from MSB
// 	for (int m=0; m<8; m++)
// 	{
// 	//	G_Val = G;
// 		G_Val = G >> m;
// 		G_Buff = G_Val & 0x01;
// 		
// 		
// 
// 		array[m] = G_Buff;
// 		
// 		PORTA = G_Buff;
// 		G_Buff = 0;
// //		G_Val = 0;
// 		
// 		
// 		_delay_ms(500);   
// 		
// 	}

 
	
	// using delays can make you understand whats in the data register, but it may in some cases break the code, and in this case it did.
	
	
// 	for (int i=0; i<14; i++)
// 	{
// 		data |= array[n1++];
// 		data = data << 1;
// 		PORTA = data;
// 		_delay_ms(100);
// 	}
	
	
	
	
	Code = array[0];
	
	while (1)
	{

// 				 B++;
 		 		
		

//TIMSK1 &= ~(1<<OCIE1A);	 //	cli();
// 															for (int L1=0; L1<2)
// 															{
																	while (n<LED_NUM) // at 24 its working
																//	while (1)
																	{
			
					
																				if (Code == 1)
																				{
																					// code 1
																					PORTC = 0xff;
								
																//				_delay_us(0.7);
																				asm volatile (
																				"    ldi  r25, 4	\n"
																				"1:  dec  r25	\n"
																				"    brne 1b	\n"
																				"    rjmp 1f	\n"
																				"1:	\n"
																				);
	
																					PORTC = 0x00;
								
																	//				_delay_us(0.6); // compiler optimization is none to make below ASM to work, but only for 600 nS, actually it didnt work i guess
																			// after trial and error, i added 300nS + 300nS in Assembly
																			asm volatile (
																			"    ldi  r25, 4	\n"
																			"1:  dec  r25	\n"
																			"    brne 1b	\n"
																			);



// 													 for (int x=0; x<9; x++)
// 													 {
// 													 }

								
																					n++;
																					Code = array[n];		// another method is by down counting n by 24, n--
																				}

																						if (Code == 0)
																						{
																							// code 0
				
																							PORTC = 0xff;
										
																			//				_delay_us(0.35);
																							asm volatile (
																							"    lpm	\n"
																							"    lpm	\n"
																							"    nop	\n"
																							);										            
																							PORTC = 0x00;
										
																			//				_delay_us(0.8);
																							asm volatile (
																							"    ldi  r25, 5	\n"
																							"1:  dec  r25	\n"
																							"    brne 1b	\n"
																							"    nop	\n"
																							);
				
																							n++;
																							Code = array[n];
																						}
			
																				//		PORTA = 0x80;
		
																	}
				
		//		m1=0;
				PORTA ^= 1<<PINA7;
				
										if (Color_Flag == 1)
										{
											for(char L=0; L<Leds; L++)
											{
												
															////////////////////////////////////////// this starts from MSB -> noninverting
														for (int mG=7; mG>=0; mG--) // >=, = is necessary
														{
															G_Val = G >> mG;
															//G_Val = G << 1;
															G_Buff = (G_Val & 0x01); // another method is by using & 0x02 and then right shifting(>>) it.

															array[m1] = G_Buff;
												
															PORTA |= G_Buff;
															PORTA ^= 1<<PINA7;
												
															m1++;
															G_Buff = 0;
												
															//		_delay_ms(100);
												
														}

											
														for (int mR=7; mR>=0; mR--)
														{
															R_Val = R >> mR;
															//R_Val = R << 1;
															R_Buff = (R_Val & 0x01); // another method is by using & 0x02 and then right shifting(>>) it.

															array[m1] = R_Buff;
												
															PORTA |= R_Buff;
															PORTA ^= 1<<PINA7;
												
															m1++;
															R_Buff = 0;
												
															//		_delay_ms(100);
												
														}
											
											
														for (int mB=7; mB>=0; mB--)
														{
															B_Val = B >> mB;
															//B_Val = B << 1;
															B_Buff = (B_Val & 0x01); // another method is by using & 0x02 and then right shifting(>>) it.
														//	B_Buff = B_Buff>>1;
															
															array[m1] = B_Buff;
												
															PORTA |= B_Buff;
															PORTA ^= 1<<PINA7;
												
															m1++;
															B_Buff = 0;
												
															//		_delay_ms(100);
												
														}
											
													//	m1=0;
														
											
														R_Val = 0;
														G_Val = 0;
														B_Val = 0;
											

											
											
										}
									//	Color_Flag = 0;
									}
										
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////										
										// comment this part - Application layer
									if (V==0)
									{
									R=0xff;
									G=0x00;
									B=0x00;
									}
										
									if (V==1)
									{
										R=0x00;
										G=0xff;
										B=0x00;
									}
									
									
									if (V==2)
									{
										R=0x00;
										G=0x00;
										B=0xff;
										V=-1;
									}
									V++;	
										// comment this part - Application layer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////					
					
				
//TIMSK1 |= 1<<OCIE1A;	//		sei();
				
			//	n=0;
				
// 						for (uint16_t y=0; y<50000; y++)
// 				  				{
// 				  				}
// 												for (uint16_t y=0; y<50000; y++)
// 												{
// 												}
// 					
									Code = array[0];
									n=0;
									m1 =0;
							//	  Color_Flag = 1;
								  
//_delay_ms(100);
								  
// 				LED_NUMC++;
// 				
// 				if (LED_NUMC >= Leds)
// 				{
// 					LED_NUM = 0;
// 				}

//PORTA ^= 1<<PINA5;	

_delay_ms(1000);
	}
			
}
// 
		 			 			 			 		 	// 		 			 		ISR(TIMER1_COMPA_vect)
		 			 			 			 		 	// 		 			 			 			 			{
		 			 			 			 		 	// 		 			 			 			 				Color_Flag = 1;
		 			 			 			 		 	// 		 			 			 			 	
		 			 			 			 		 	// 		 			 			 			 					n=0;
		 			 			 			 		 	// 		 			 			 			 			 		
		 			 			 			 		 	// 		 			 			 			 			 		if (R>254)
		 			 			 			 		 	// 		 			 			 			 			 		{
		 			 			 			 		 	// 		 			 			 			  					R=0;
		 			 			 			 		 	// 		 			 			 			 					G=0;
		 			 			 			 		 	// 		 			 			 			 						B=0;
		 			 			 			 		 	// 		 			 			 			 					}
		 			 			 			 		 	// 		 			 			 			 					
		 			 			 			 		 	// 		 			 			 			  				PORTA ^= 1<<PINA6;
		 			 			 			 		 	// 		 			 			 			 		 	}