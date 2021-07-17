
#include <stdio.h>
//分手信自动生成器
enum response_type { DUMP, SECOND_CHANCE, MARRIAGE };
typedef struct {
    char* name;
    enum response_type type; //在每条回复数据中记录回复类型
}response;

//发送三种类型的回复,每条回复都要保存回复类型,使用新数据类型response时需要根据回复类型分别调用三个函数
void dump(response r) {
    printf("Dear %s,\n", r.name);
    puts("unfortunately your last date contacted us to");
    puts("say that they will not be seeing you again");
}
void second_chance(response r) {
    printf("Dear %s,\n", r.name);
    puts("Good news: your last date has asked us to");
    puts("arrange another meeting.please call ASAp ");
}
void marriage(response r) {
    printf("Dear %s,\n", r.name);
    puts("Congratulations! Your last date has contacted ");
    puts("us with a proposal of marriage.");
}


void (*replies[])(response) = { dump,second_chance,marriage };


int main() {
    response r[] = {
               {"Mike",DUMP},{"Luis",SECOND_CHANCE },
               {"Matt",SECOND_CHANCE},{"Wliliam",MARRIAGE}
    };
    int i;
    for (i = 0; i < 4; i++) {
        replies[r[i].type](r[i]);   //(r[i])调用函数并把数据传给它
    }
}


