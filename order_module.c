//
// Created by H on 2026/3/10.
//
#include "include Milktea House Management.h"

//生成订单编号 (格式:O+ 年月日时分 + 序号)
void generate_order_id(char *order_id) {
    static int seq = 1;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    sprintf(order_id, "O%04d%02d%02d%02d%02d%d",
            tm_info->tm_year + 1900,
            tm_info->tm_mon + 1,
            tm_info->tm_mday,
            tm_info->tm_hour,
            tm_info->tm_min,
            seq++);
}

//创建订单功能（支持一个订单包含多种饮品
void create_order() {
    char order_id[20];
   int n;
    
    printf("\n【创建订单】\n");
    
    // 生成订单编号
    generate_order_id(order_id);
    printf("订单编号：%s\n", order_id);
    
    printf("饮品数量：");
    scanf("%d", &n);
    
    if(n <= 0) {
        printf("饮品数量不能小于 0\n");
        return;
    }
    
    // 循环录入每种饮品
    for(int i = 0; i < n; i++) {
        OrderRecord o;
        
        strcpy(o.order_id, order_id);
        
        printf("\n第 %d 种饮品编号：", i + 1);
        scanf("%s", o.drink_id);
        
        // 验证饮品是否存在
       int index = find_drink(o.drink_id);
        if(index == -1) {
            printf("饮品不存在！\n");
            i--;
            continue;
        }
        
        printf("数量：");
        scanf("%d", &o.order_num);
        
        if(o.order_num <= 0) {
            printf("数量不能小于 0\n");
            i--;
            continue;
        }
        
        // 获取当前时间
        time_t t = time(NULL);
        strftime(o.order_time, sizeof(o.order_time), "%Y-%m-%d_%H:%M", localtime(&t));
        
        // 计算总价
        o.total_amount = drinks[index].price * o.order_num;
        
        // 更新状态：未开始
        o.order_status = 0;
        
        // 添加到订单列表
        orders[order_count++] = o;
        
        printf("添加成功\n");
    }
    
    printf("\n订单创建成功\n");
}

//开始制作订单（检查原料库存并扣减
void start_order() {
    char id[20];
   int found = 0;
    
    printf("\n【开始制作】\n");
    printf("订单编号：");
    scanf("%s", id);
    
    for(int i = 0; i < order_count; i++) {
        if(strcmp(orders[i].order_id, id) == 0) {
            
            // 检查订单状态
            if(orders[i].order_status == 2) {
                printf("该订单已完成，无法修改！\n");
                return;
            }
            
            // 查找饮品并扣减原料
           int drink_idx = find_drink(orders[i].drink_id);
            if(drink_idx != -1) {
                if(!deduct_material(drink_idx, orders[i].order_num)) {
                    printf("原料不足，无法开始制作！\n");
                    return;
                }
            }
            
            // 更新状态：制作中
            orders[i].order_status = 1;
            found = 1;
        }
    }
    
    if(found) {
        printf("订单已开始制作\n");
    } else {
        printf("错误：订单不存在！\n");
    }
}

//完成订单
void finish_order() {
    char id[20];
   int found = 0;
    
    printf("\n【完成订单】\n");
    printf("订单编号：");
    scanf("%s", id);
    
    for(int i = 0; i < order_count; i++) {
        if(strcmp(orders[i].order_id, id) == 0) {
            
            if(orders[i].order_status == 2) {
                printf("该订单已完成！\n");
                return;
            }
            
            // 更新状态：已完成
            orders[i].order_status = 2;
            found = 1;
        }
    }
    
    if(found) {
        printf("订单已完成\n");
    } else {
        printf("错误：订单不存在！\n");
    }
}

//查询待制作订单
void pending_orders() {
    printf("\n【待制作订单】\n");
    printf("------------------------------------------------------------\n");
    printf("%-15s %-10s %-8s %-8s %s\n", 
           "订单编号", "饮品", "数量", "总价", "状态");
    printf("------------------------------------------------------------\n");
    
   int count = 0;
    for(int i = 0; i < order_count; i++) {
        if(orders[i].order_status == 0) {
            printf("%-15s %-10s %-8d %-8.2f 未开始\n",
                   orders[i].order_id,
                   orders[i].drink_id,
                   orders[i].order_num,
                   orders[i].total_amount);
            count++;
        }
    }
    
    if(count == 0) {
        printf("暂无待制作订单\n");
    }
    
    printf("------------------------------------------------------------\n");
}