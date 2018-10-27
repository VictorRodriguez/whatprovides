#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>
#include <stdlib.h>

struct url_data {
    size_t size;
    char* data;
};


size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size += (size * nmemb);

#ifdef DEBUG
    fprintf(stderr, "data at %p size=%ld nmemb=%ld\n", ptr, size, nmemb);
#endif
    tmp = realloc(data->data, data->size + 1); /* +1 for '\0' */

    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}

char *download_dnf(){
    struct url_data data;
    data.size = 0;
    data.data = malloc(4096);
    if(NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/clearlinux/common/master/conf/dnf.conf");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    res = curl_easy_perform(curl);
    printf("IM IN");
    if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }
    return data.data;
}

void print_help(char** argv){

    printf("\nUse this binary to search what pkg provides a binary\n");
    printf("\ni.e.:\n");
    printf("\n    %s /usr/bin/ls\n\n",argv[0]);

}

int main (int argc, char** argv){

    const char *fname = "/etc/dnf.conf";
    if( access( fname, F_OK ) != -1 ) {
        if (argc>=2){
        char *const parmlist[] = {"/usr/bin/dnf-3", "--releasever=clear",\
            "--config=/etc/dnf.conf","provides",argv[1],NULL};
        execv("/usr/bin/dnf-3",parmlist);
        } else{
            print_help(argv);
            return -1;
        }
    } else {

        perror("dnf.conf does not exist in /etc/, please copy there");
        perror("this is the file:");
        char* data;
        data = download_dnf();
        if(data) {
            printf("%s",data);
        }
        return -1;
    }

    return 0;

}

