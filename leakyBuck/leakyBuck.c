#include <stdio.h>

int main() {
    int incoming, outgoing, buck_size, n, store = 0;

    printf("Enter bucket size, outgoing rate and no of inputs: ");
    scanf("%d %d %d", &buck_size, &outgoing, &n);

    while (n != 0) {
        printf("\nEnter the incoming packet size: ");
        scanf("%d", &incoming);
        printf("Incoming packet size: %d\n", incoming);

        if (incoming <= (buck_size - store)) {
            store += incoming;
            printf("Bucket buffer size: %d out of %d\n", store, buck_size);
        } else {
            printf("Dropped %d packets\n", incoming - (buck_size - store));
            store = buck_size; // Bucket fills up completely
            printf("Bucket buffer size: %d out of %d\n", store, buck_size);
        }

        // Corrected outgoing logic
        store -= outgoing;
        if (store < 0) store = 0;

        printf("After outgoing, there are %d packets left in buffer\n", store);

        n--;
    }

    return 0;
}
