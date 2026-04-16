//
// Created by H on 2026/3/10.
//
#include "include Milktea House Management.h"

// 查找原料
int find_material(char id[]) {
    for(int i = 0; i < material_count; i++) {
        if(strcmp(materials[i].material_id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// 生成记录编号
void generate_record_id(char *record_id) {
    static int seq = 1;
    time_t t = time(NULL);
    sprintf(record_id, "R%ld%d", (long)t, seq++);
}

//添加原料功能
void add_material() {
    Material m;

    printf("\n【添加原料】\n");

    printf("原料编号 (如 M001): ");
    scanf("%s", m.material_id);

    if(find_material(m.material_id) != -1) {
        printf("错误：原料编号已存在！\n");
        return;
    }

    printf("原料名称 (如 珍珠): ");
    scanf("%s", m.material_name);

    printf("初始库存量：");
    scanf("%f", &m.stock_quantity);

    printf("最低库存预警线：");
    scanf("%f", &m.min_stock);

    printf("单位成本 (元): ");
    scanf("%f", &m.unit_cost);

    printf("计量单位 (g/ml/kg/L/个): ");
    scanf("%s", m.unit);

    // 记录时间
    time_t t = time(NULL);
    strftime(m.last_update, sizeof(m.last_update), "%Y-%m-%d_%H:%M", localtime(&t));

    // 添加到数组
    materials[material_count++] = m;

    // 创建入库记录
    MaterialRecord rec;
    generate_record_id(rec.record_id);
    strcpy(rec.material_id, m.material_id);
    strcpy(rec.operation_type, "ADD");
    rec.quantity = m.stock_quantity;
    strcpy(rec.operation_time, m.last_update);
    strcpy(rec.related_order, "-");
    material_records[material_record_count++] = rec;

    printf("原料添加成功！\n");
}

//显示原料库存
void show_materials() {
    printf("\n【原料库存】\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-12s %-10s %-8s %-10s %s\n",
           "编号", "名称", "库存", "预警线", "成本", "单位", "状态");
    printf("--------------------------------------------------------------------------------\n");

    if(material_count == 0) {
        printf("暂无原料数据\n");
    } else {
        for(int i = 0; i < material_count; i++) {
            const char *status = materials[i].stock_quantity <= materials[i].min_stock
                                 ? "预警" : "充足";
            //条件判断 小于等于预警值materials[i].min_stock则“预警”

            printf("%-10s %-15s %-12.2f %-10.2f %-8.2f %-10s %s\n",
                   materials[i].material_id,
                   materials[i].material_name,
                   materials[i].stock_quantity,
                   materials[i].min_stock,
                   materials[i].unit_cost,
                   materials[i].unit,
                   status);
        }
    }

    printf("--------------------------------------------------------------------------------\n");
}

//原料补货功能
void replenish_material() {
    char id[10];
    float quantity;

    printf("\n【原料补货】\n");
    printf("原料编号：");
    scanf("%s", id);
    //
   int index = find_material(id);
    if(index == -1) {
        printf("错误：原料不存在！\n");
        return;
    }

    printf("补货数量：");
    scanf("%f", &quantity);
    //防止输入错误导致崩溃
    if(quantity <= 0) {
        printf("错误：补货数量必须大于 0！\n");
        return;
    }

    // 增加库存
    materials[index].stock_quantity += quantity;

    // 更新时间
    time_t t = time(NULL);
    strftime(materials[index].last_update, sizeof(materials[index].last_update),
             "%Y-%m-%d_%H:%M", localtime(&t));

    // 创建补货记录
    MaterialRecord rec;
    generate_record_id(rec.record_id);
    strcpy(rec.material_id, id);
    strcpy(rec.operation_type, "ADD");
    rec.quantity = quantity;
    strcpy(rec.operation_time, materials[index].last_update);
    strcpy(rec.related_order, "-");
    material_records[material_record_count++] = rec;

    printf("补货成功！当前库存：%.2f%s\n",
           materials[index].stock_quantity, materials[index].unit);
}

//查询原料功能
void query_material() {
   int choice;
    char keyword[30];

    printf("\n【查询原料】\n");
    printf("1. 按编号查询\n");
    printf("2. 按名称查询\n");
    printf("选择：");
    scanf("%d", &choice);

    if(choice == 1) {
        printf("原料编号：");
        scanf("%s", keyword);
       //调用查找函数 遍历查找 没找到就返回-1，找到就返回索引
       int index = find_material(keyword);
        if(index == -1) {
            printf("未找到该原料\n");
            return;
        }

        printf("\n详细信息:\n");
        printf("编号：%s\n", materials[index].material_id);
        printf("名称：%s\n", materials[index].material_name);
        printf("库存：%.2f%s\n", materials[index].stock_quantity, materials[index].unit);
        printf("预警线：%.2f%s\n", materials[index].min_stock, materials[index].unit);
        printf("成本：%.2f 元/%s\n", materials[index].unit_cost, materials[index].unit);
        printf("更新：%s\n", materials[index].last_update);

    } else if(choice == 2) {
        printf("原料名称: ");
        scanf("%s", keyword);

       int found = 0;
        printf("\n查询结果:\n");
        for(int i = 0; i < material_count; i++) {
            if(strstr(materials[i].material_name, keyword) != NULL) {
                printf("%-10s %-15s %.2f%s %s\n",
                       materials[i].material_id,
                       materials[i].material_name,
                       materials[i].stock_quantity,
                       materials[i].unit,
                       materials[i].stock_quantity <= materials[i].min_stock ? "不足" : "充足");
                found++;
            }
        }

        if(found == 0) {
            printf("未找到匹配的原料\n");
        } else {
            printf("共找到 %d 条记录\n", found);
        }
    }
}

int deduct_material(int drink_index, int quantity) {
    // 假设每杯饮品消耗固定量的基础原料
    char base_material_id[] = "M001";  // 假设 M001 是基础原料
   int mat_index = find_material(base_material_id);

    if(mat_index != -1) {
        float needed = 50.0 * quantity;  // 每杯消耗 50ml

        if(materials[mat_index].stock_quantity < needed) {
            printf("??  原料【%s】库存不足！需要%.2f，当前%.2f\n",
                   materials[mat_index].material_name,
                   needed,
                   materials[mat_index].stock_quantity);
            return 0;
        }

        // 扣减库存
        materials[mat_index].stock_quantity -= needed;

        // 更新时间
        time_t t = time(NULL);
        strftime(materials[mat_index].last_update, sizeof(materials[mat_index].last_update),
                 "%Y-%m-%d_%H:%M", localtime(&t));

        // 创建使用记录
        MaterialRecord rec;
        generate_record_id(rec.record_id);
        strcpy(rec.material_id, base_material_id);
        strcpy(rec.operation_type, "USE");
        rec.quantity = needed;
        strcpy(rec.operation_time, materials[mat_index].last_update);
        strcpy(rec.related_order, "-");
        material_records[material_record_count++] = rec;
    }

    return 1;
}

//库存预警检查
void check_stock_warning() {
    printf("\n【库存预警检查】\n");
    printf("------------------------------------------------------------\n");

   int warning_count = 0;

    for(int i = 0; i < material_count; i++) {
        if(materials[i].stock_quantity <= materials[i].min_stock) {
            printf("??  【%s】库存告急！\n", materials[i].material_name);
            printf("   当前：%.2f%s, 预警：%.2f%s\n",
                   materials[i].stock_quantity,
                   materials[i].unit,
                   materials[i].min_stock,
                   materials[i].unit);
            printf("   建议立即补货！\n\n");
            warning_count++;
        }
    }

    if(warning_count == 0) {
        printf("所有原料库存充足\n");
    } else {
        printf("共有 %d 种原料需要补货\n", warning_count);
    }
}

//原料统计功能
void material_statistics() {
   int choice;

    printf("\n【原料统计】\n");
    printf("1. 原料使用统计\n");
    printf("2. 库存成本统计\n");
    printf("3. 补货记录统计\n");
    printf("选择：");
    scanf("%d", &choice);

    if(choice == 1) {
        printf("\n原料使用统计:\n");
        for(int i = 0; i < material_count; i++) {
            float total_used = 0;

            for(int j = 0; j < material_record_count; j++) {
                if(strcmp(material_records[j].material_id, materials[i].material_id) == 0 &&
                   strcmp(material_records[j].operation_type, "USE") == 0) {
                    total_used += material_records[j].quantity;
                }
            }

            printf("%s (%s): 累计使用 %.2f%s\n",
                   materials[i].material_name,
                   materials[i].material_id,
                   total_used,
                   materials[i].unit);
        }

    } else if(choice == 2) {
        printf("\n库存成本统计:\n");
        float total_value = 0;

        for(int i = 0; i < material_count; i++) {
            float value = materials[i].stock_quantity * materials[i].unit_cost;
            total_value += value;

            printf("%s: %.2f%s × %.2f 元 = %.2f 元\n",
                   materials[i].material_name,
                   materials[i].stock_quantity,
                   materials[i].unit,
                   materials[i].unit_cost,
                   value);
        }

        printf("\n库存总价值：%.2f 元\n", total_value);

    } else if(choice == 3) {
        printf("\n近期补货记录:\n");
       int count = 0;

        for(int i = material_record_count - 1; i >= 0 && count < 10; i--) {
            if(strcmp(material_records[i].operation_type, "ADD") == 0) {
                printf("%s | %s | +%-.2f | %s\n",
                       material_records[i].operation_time,
                       material_records[i].material_id,
                       material_records[i].quantity,
                       material_records[i].record_id);
                count++;
            }
        }

        if(count == 0) {
            printf("暂无补货记录\n");
        }
    }
}