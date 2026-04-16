#include "include Milktea House Management.h"

int find_drink(char id[]) {
    for(int i = 0; i < drink_count; i++) {
        if(strcmp(drinks[i].drink_id, id) == 0) {
            return i;
        }
    }
    return -1;
}

//添加饮品功能依次录入：编号→名称→规格→价格→配料
void add_drink() {
    Drink d;

    printf("\n【添加新饮品】\n");

    printf("饮品编号 (如 D001): ");
    scanf("%s", d.drink_id);

    // 检查编号唯一性（遍历查找）（不等于-1 则已有）
    if(find_drink(d.drink_id) != -1) {
        printf("错误：饮品编号已存在！\n");
        return;
    }

    printf("饮品名称 (如 珍珠奶茶): ");
    scanf("%s", d.drink_name);

    printf("规格 (大/中/小): ");
    scanf("%s", d.spec);

    printf("价格 (元): ");
    scanf("%f", &d.price);

    printf("配料说明 (如 珍珠，椰果，布丁): ");
    scanf("%s", d.ingredients);

    // 添加到数组
    drinks[drink_count++] = d;

    printf("添加成功！\n");
}

//显示所有饮品 以文本文档形式展示饮品列表（同时通过设定每个字符的宽度 确保文本的整齐美观）
void show_drinks() {
    printf("\n【饮品列表】\n");
    printf("------------------------------------------------------------\n");
    printf("%-10s %-20s %-8s %-8s %s\n",
           "编号", "名称", "规格", "价格", "配料");
    printf("------------------------------------------------------------\n");

    if(drink_count == 0) {
        printf("暂无饮品数据\n");
    } else {
        for(int i = 0; i < drink_count; i++) {
            printf("%-10s %-20s %-8s %-8.2f %s\n",
                   drinks[i].drink_id,
                   drinks[i].drink_name,
                   drinks[i].spec,
                   drinks[i].price,
                   drinks[i].ingredients);
        }
    }

    printf("------------------------------------------------------------\n");
    printf("共 %d 种饮品\n", drink_count);
}