#include<stdio.h>
#include<time.h>
void shuchu(FILE *f,time_t a ,time_t b,char c[],char d[],char e[],char g[],char *h,char *i)
{
    struct tm shijiana,shijianb;
    localtime_s(&shijiana,&a);
    localtime_s(&shijianb,&b);

    fprintf(f, "BEGIN:VEVENT\n");
    fprintf(f, "UID:%d%d%dCOS\n",shijiana.tm_year + 1900,shijiana.tm_mon + 1,shijiana.tm_mday);
    fprintf(f, "DTSTART;VALUE=DATE:%04d%02d%02d\n",shijiana.tm_year + 1900,shijiana.tm_mon + 1,shijiana.tm_mday);
    fprintf(f, "DTEND;VALUE=DATE:%04d%02d%02d\n",shijianb.tm_year + 1900,shijianb.tm_mon + 1,shijianb.tm_mday);
    fprintf(f, "SUMMARY:%s%s日 %s %s\n",c,d,e,g);
    fprintf(f, "DESCRIPTION:天干: %s ,属性: %s ,含义: %s ,地支: %s ,属性: %s ,含义: %s\n",c,e,h,d,g,i);
    fprintf(f, "END:VEVENT\n\n");
}
    char *tianganhanyi[] = {"栋梁之木，代表生长、开端","花草之木，代表柔顺、弯曲","太阳之火，代表光明、热烈","灯烛之火，代表文明、精微","城墙之土，代表厚重、稳固","田园之土，代表包容、孕育","斧钺之金，代表刚健、变革","首饰之金，代表温润、精致","江河之水，代表奔放、流动","雨露之水，代表闭藏、滋润"};
    char *dizhihanyi[] =  {"阳水，坎水。象征生命的萌芽与开端。代表流动性、隐秘性、智慧、危机（子夜最暗，也孕育光明）。","湿土，冻土。象征联结与承载。是金库，内藏癸水、辛金。代表静止、孕育、坚守、艰难（牛的特性）。","阳木，栋梁之木。象征生长与突破。代表开始、活力、领导力、冒险精神（虎的特性）。","阴木，花草之木。象征繁茂与柔韧。代表温和、细腻、繁殖、门户（日出卯时，门户开）。","湿土，水库。象征变化与灵动。内藏乙木、癸水，是“泥中之龙”。代表动荡、机遇、聚合（龙能聚云雨）。","阴火，温暖之火。象征变化与智慧。代表曲折、灵巧、文化、隐匿（蛇的特性）。","阳火，太阳之火。象征鼎盛与光明。代表热情、力量、顶峰、但也含藏危险（物极必反）。","燥土，木库。象征收获与包容。内藏丁火、乙木。代表温情、收获、家庭、谦和（羊的特性）。","阳金，刚健之金。象征肃杀与敏捷。代表变革、锋利、机敏、传送（猴的特性）。","阴金，精致之金。象征收敛与圆满。代表完成、精致、沉默、肃杀（秋收后万物萧条）。","燥土，火库。象征收藏与忠诚。内藏辛金、丁火。代表仓库、忠诚、结束、防卫（狗的特性）。","阴水，江河之水。象征终结与回归。代表结束、收藏、奔流、也是新循环的孕育（位于末位，孕下一轮“子”）。"};
    char tiangan[10][4] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
    char dizhi[12][4] = {"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"};
    char tinagan_shuxing[10][7] = {"阳木","阴木","阳火","阴火","阳土","阴土","阳金","阴金","阳水","阴水"};
    char dizhi_shuxing[12][7] = {"阳水","湿土","阳木","阴木","湿土","阴火","阳火","燥土","阳金","阴金","燥土","阴水"};

int main()
{   

    int miaoshu = 86400;
    struct tm time_1;
    time_t t1 = time(NULL);
    localtime_s(&time_1,&t1);
    FILE *file = fopen("shuxing.ics","w");
    printf ("%d年,%d月,%d日\n",time_1.tm_year + 1900,time_1.tm_mon + 1,time_1.tm_mday);
    fprintf(file, "BEGIN:VCALENDAR\n");
    fprintf(file, "VERSION:2.0\n");
    fprintf(file, "X-WR-CALNAME:天干地支\n");
    fprintf(file, "PRODID:Cos\n");
    fprintf(file, "CALSCALE:GREGORIAN\n");
    fprintf(file, "METHOD:REQUEST\n\n");
    for (int i = 0; i < 366; i++)
    {   
        int b = 0,c = 0,a = 0;
        localtime_s(&time_1,&t1);
        printf ("%d年%d月%d日\n",time_1.tm_year + 1900,time_1.tm_mon + 1,time_1.tm_mday);
        b = ((t1 - 1736035200) / 86400) % 10;
        c = ((t1 - 1736208020) / 86400) % 12;
        printf("%s%s日 %s %s\n",tiangan[b],dizhi[c],tinagan_shuxing[b],dizhi_shuxing[c]);
        t1 += miaoshu;
        a = t1 - 86400;

        shuchu(file,a,t1,tiangan[b],dizhi[c],tinagan_shuxing[b],dizhi_shuxing[c],tianganhanyi[b],dizhihanyi[c]);
    } 
    fprintf(file, "END:VCALENDAR\n");
    fclose(file);
    return 0;
}