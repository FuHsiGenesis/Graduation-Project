#ifndef SMBUS_CM_H
#define SMBUS_CM_H


void start_bit();
void stop_bit();
void send_bit(unsigned char bit_out);
unsigned char receive_bit();
unsigned char slave_ack();
void TX_byte(unsigned char TX_buffer);
unsigned char RX_byte(unsigned char ack_nack);


#endif
