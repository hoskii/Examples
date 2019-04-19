#include <pthread.h>
class CountDownLatch{
public:
    explicit CountDownLatch(int count):count(count),mutex(PTHREAD_MUTEX_INITIALIZER),cond(PTHREAD_COND_INITIALIZER){}

    void wait(){
        pthread_mutex_lock(&mutex);
        while(count > 0)
            pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }

    void countDown(){
        pthread_mutex_lock(&mutex);
        --count;
        if(count == 0)
            pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

private:
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};
