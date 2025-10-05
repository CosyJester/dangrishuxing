#include<stdio.h>
#include<time.h>
void shuchu(FILE *f,time_t a ,time_t b,char c[],char d[],char e[],char g[])
{
    struct tm shijiana,shijianb;
    localtime_s(&shijiana,&a);
    localtime_s(&shijianb,&b);

    fprintf(f, "BEGIN:VEVENT\n");
    fprintf(f, "UID:%d%d%dCOS\n",shijiana.tm_year + 1900,shijiana.tm_mon + 1,shijiana.tm_mday);
    fprintf(f, "DTSTART;VALUE=DATE:%04d%02d%02d\n",shijiana.tm_year + 1900,shijiana.tm_mon + 1,shijiana.tm_mday);
    fprintf(f, "DTEND;VALUE=DATE:%04d%02d%02d\n",shijianb.tm_year + 1900,shijianb.tm_mon + 1,shijianb.tm_mday);
    fprintf(f, "SUMMARY:%s%s日 %s %s\n",c,d,e,g);
    fprintf(f, "END:VEVENT\n\n");
}

int main()
{   

    char tiangan[10][4] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
    char dizhi[12][4] = {"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"};
    char tinagan_shuxing[10][7] = {"阳木","阴木","阳火","阴火","阳土","阴土","阳金","阴金","阳水","阴水"};
    char dizhi_shuxing[12][7] = {"阳水","湿土","阳木","阴木","湿土","阴火","阳火","燥土","阳金","阴金","燥土","阴水"};
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

        shuchu(file,a,t1,tiangan[b],dizhi[c],tinagan_shuxing[b],dizhi_shuxing[c]);
    } 
    fprintf(file, "END:VCALENDAR\n");
    fclose(file);
    return 0;
}