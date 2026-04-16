//
// Created by H on 2026/3/10.
//
#include <windows.h>
#include "include Milktea House Management.h"

//确保 GBK 格式存储 避免后续出现问题
void save_data() {
    //确保 GBK 格式存储 避免后续出现问题
    SetConsoleOutputCP(936);
    FILE *fp;
    
    // 确保数据目录存在
    CreateDirectoryA("data", NULL);
    
    // 保存饮品数据
    fp = fopen(DATA_DIR "drinks.txt", "w");
    if(fp != NULL) {
        for(int i = 0; i < drink_count; i++) {
            fprintf(fp, "%s|%s|%s|%.2f|%s\n",
                    drinks[i].drink_id,
                    drinks[i].drink_name,
                    drinks[i].spec,
                    drinks[i].price,
                    drinks[i].ingredients);
        }
        fclose(fp);
    }
    
    // 保存订单数据
    fp = fopen(DATA_DIR "orders.txt", "w");
    if(fp != NULL) {
        for(int i = 0; i < order_count; i++) {
            fprintf(fp, "%s|%s|%s|%d|%.2f|%d\n",
                    orders[i].order_id,
                    orders[i].drink_id,
                    orders[i].order_time,
                    orders[i].order_num,
                    orders[i].total_amount,
                    orders[i].order_status);
        }
        fclose(fp);
    }
    
    // 保存原材料数据
    fp = fopen(DATA_DIR "materials.txt", "w");
    if(fp != NULL) {
        for(int i = 0; i < material_count; i++) {
            fprintf(fp, "%s|%s|%.2f|%.2f|%.2f|%s|%s\n",
                    materials[i].material_id,
                    materials[i].material_name,
                    materials[i].stock_quantity,
                    materials[i].min_stock,
                    materials[i].unit_cost,
                    materials[i].unit,
                    materials[i].last_update);
        }
        fclose(fp);
    }
    
    // 保存原材料记录
    fp = fopen(DATA_DIR "material_records.txt", "w");
    if(fp != NULL) {
        for(int i = 0; i < material_record_count; i++) {
            fprintf(fp, "%s|%s|%s|%.2f|%s|%s\n",
                    material_records[i].record_id,
                    material_records[i].material_id,
                    material_records[i].operation_type,
                    material_records[i].quantity,
                    material_records[i].operation_time,
                    material_records[i].related_order);
        }
        fclose(fp);
    }
    
    printf("数据已保存在 data/ 目录\n");
}

//文件读取函数
void load_data() {
    // 设置控制台输出为 GBK
    SetConsoleOutputCP(936);

    FILE *fp;
    
    // 读取饮品数据
    fp = fopen(DATA_DIR "drinks.txt", "r");
    if(fp != NULL) {
        while(fscanf(fp, "%[^|]|%[^|]|%[^|]|%f|%s\n",
                     drinks[drink_count].drink_id,
                     drinks[drink_count].drink_name,
                     drinks[drink_count].spec,
                     &drinks[drink_count].price,
                     drinks[drink_count].ingredients) == 5) {
            drink_count++;
        }
        fclose(fp);
        printf("已读取 %d 杯饮品\n", drink_count);
    }
    
    // 读取订单数据
    fp = fopen(DATA_DIR "orders.txt", "r");
    if(fp != NULL) {
        while(fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%f|%d\n",
                     orders[order_count].order_id,
                     orders[order_count].drink_id,
                     orders[order_count].order_time,
                     &orders[order_count].order_num,
                     &orders[order_count].total_amount,
                     &orders[order_count].order_status) == 6) {
            order_count++;
        }
        fclose(fp);
        printf("已读取 %d 条订单\n", order_count);
    }
    
    // 读取原材料数据
    fp = fopen(DATA_DIR "materials.txt", "r");
    if(fp != NULL) {
        while(fscanf(fp, "%[^|]|%[^|]|%f|%f|%f|%[^|]|%s\n",
                     materials[material_count].material_id,
                     materials[material_count].material_name,
                     &materials[material_count].stock_quantity,
                     &materials[material_count].min_stock,
                     &materials[material_count].unit_cost,
                     materials[material_count].unit,
                     materials[material_count].last_update) == 7) {
            material_count++;
        }
        fclose(fp);
        printf("已读取 %d 种原材料\n", material_count);
    }
    
    // 读取原材料记录
    fp = fopen(DATA_DIR "material_records.txt", "r");
    if(fp != NULL) {
        while(fscanf(fp, "%[^|]|%[^|]|%[^|]|%f|%[^|]|%s\n",
                     material_records[material_record_count].record_id,
                     material_records[material_record_count].material_id,
                     material_records[material_record_count].operation_type,
                     &material_records[material_record_count].quantity,
                     material_records[material_record_count].operation_time,
                     material_records[material_record_count].related_order) == 6) {
            material_record_count++;
        }
        fclose(fp);
        printf("已读取 %d 条原材料记录\n", material_record_count);
    }
    
    printf("\n数据读取完成\n");
}