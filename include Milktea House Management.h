//
// Created by H on 2026/3/10.
//
#ifndef TEA_HOUSE_MANAGEMENT_INCLUDE_MILKTEA_HOUSE_MANAGEMENT_H
#define TEA_HOUSE_MANAGEMENT_INCLUDE_MILKTEA_HOUSE_MANAGEMENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ==================== 常量定义 ====================
#define MAX_DRINK 100           // 最大饮品种类数
#define MAX_ORDER 500           // 最大订单记录数
#define MAX_MATERIAL 200        // 最大原料种类数
#define MAX_RECORD 2000         // 最大原料操作记录数
#define DATA_DIR "data/"        // 数据文件存储目录

// ==================== 数据结构定义 ====================

//饮品结构体（存储奶茶产品的基本信息
typedef struct {
    char drink_id[10];          // 饮品编号（唯一标识，如：D001）
    char drink_name[30];        // 饮品名称（如：珍珠奶茶）
    char spec[5];               // 规格（大/中/小）
    float price;                // 单价（元）
    char ingredients[50];       // 配料列表（逗号分隔的原料 ID）
} Drink;

//订单结构体（记录客户订单的详细信息
typedef struct {
    char order_id[10];          // 订单编号（如：O20240101001）
    char drink_id[10];          // 饮品编号
    char order_time[20];        // 下单时间（格式：YYYY-MM-DD_HH:MM）
   int order_num;              // 订购数量
    float total_amount;         // 订单总金额
   int order_status;           // 订单状态：0-待制作，1-制作中，2-已完成
} OrderRecord;

//原料结构体（管理原材料库存信息
typedef struct {
    char material_id[10];       // 原料编号（如：M001）
    char material_name[30];     // 原料名称（如：珍珠、牛奶）
    float stock_quantity;       // 当前库存量
    float min_stock;            // 最低库存预警线
    float unit_cost;            // 单位成本（元）
    char unit[10];              // 计量单位（g/ml/kg/L/个）
    char last_update[20];       // 最后更新时间
} Material;

//原料操作记录结构体（追踪原料的出入库流水
typedef struct {
    char record_id[15];         // 记录编号（如：R001）
    char material_id[10];       // 原料编号
    char operation_type[10];    // 操作类型：ADD-入库，USE-出库
    float quantity;             // 操作数量
    char operation_time[20];    // 操作时间
    char related_order[10];     // 关联订单号（出库时填写）
} MaterialRecord;

// 全局变量声明
extern Drink drinks[MAX_DRINK];
extern OrderRecord orders[MAX_ORDER];
extern Material materials[MAX_MATERIAL];
extern MaterialRecord material_records[MAX_RECORD];

extern int drink_count;         // 饮品种类计数
extern int order_count;         // 订单记录计数
extern int material_count;      // 原料种类计数
extern int material_record_count; // 原料记录计数

//-----函数声明-----
//饮品管理模块
int find_drink(char id[]);
void add_drink();
void show_drinks();

//订单管理模块
void create_order();
void start_order();
void finish_order();
void pending_orders();

//原料管理模块
int find_material(char id[]);
void add_material();
void show_materials();
void replenish_material();
void query_material();
void material_statistics();
void check_stock_warning();
int deduct_material(int drink_index, int quantity);

//统计报表模块
//void hot_drinks();
//void timeout_warning();
//void export_report();

//数据存储模块
void save_data();
void load_data();

// 用户交互界面模块
void menu();

#endif //TEA_HOUSE_MANAGEMENT_INCLUDE_MILKTEA_HOUSE_MANAGEMENT_H