#include <stdio.h>
#include <stdlib.h>


int ack = -1; // since ack is set only after receiving a packet
int seq = 0; // Acknowledgment number and sequence number
int disconnect = 0;
char turn = 's'; // 's' for sender's turn, 'r' for receiver's turn

void sender();
void receiver();

int main() {
    while (!disconnect) {
        sender();  // Sender sends a packet
        for (int k = 1; k <= 1000000000; k++);
        receiver(); // Receiver receives the packet and sends ACK
    }
    return 0;
}

void sender() {
    if (turn == 's') { // If it's the sender's turn
        printf("SENDER: Sent packet with seq NO: %d\n", seq);

        // Simulate packet loss (1 in 4 chance of packet loss)
        if (rand() % 4 == 0) {
            printf("SENDER: Packet lost, retransmitting...\n");
            return; // If packet is lost, don't change the turn, retransmit
        }

        // Wait for the receiver to send an ACK
        turn = 'r'; // Now it's receiver's turn to receive the packet and send an ACK
    }
}

void receiver() {
    if (turn == 'r') { // If it's the receiver's turn
        printf("RECEIVER: Received packet with seq NO: %d\n", seq);

        // Simulate ACK error (1 in 4 chance of ACK failure)
        if (rand() % 4 == 0) {
            printf("RECEIVER: Failed to send ACK for seq NO: %d\n", seq);
            turn = 's'; // Give turn back to sender for retransmission
            return;
        }

        ack = seq; // Send ACK for the received packet
        printf("RECEIVER: Sent ACK for seq NO: %d\n", ack);

        // Give turn back to sender to process the ACK
        turn = 's'; // Now it's sender's turn again
    }

    // After the receiver sends an ACK, the sender needs to acknowledge it
    if (turn == 's' && ack == seq) {
        printf("SENDER: Acknowledged ACK for seq NO: %d\n", ack);
        seq++; // Move to the next sequence number
        if (seq == 5) {  // Once 5 packets are sent, disconnect
            disconnect = 1;
        }
    }
}
