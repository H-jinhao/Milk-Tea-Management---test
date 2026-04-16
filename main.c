#include "include Milktea House Management.h"

Drink drinks[MAX_DRINK];
OrderRecord orders[MAX_ORDER];
Material materials[MAX_MATERIAL];
MaterialRecord material_records[MAX_RECORD];

int drink_count = 0;
int order_count = 0;
int material_count = 0;
int material_record_count = 0;

//主函数 - 程序入口（该函数负责程序的启动、数据初始化、以及用户交互
int main() {
  int choice;

    // 设置控制台编码为 GBK 以防止中文乱码
    SetConsoleOutputCP(936);

    // 刷新控制台缓冲区以确保编码设置生效
    system("");

    // 加载历史数据
    load_data();

   printf("\n================================\n");
   printf("  欢迎使用奶茶店订单管理系统\n");
   printf("================================\n\n");

    //功能选择
    while(1) {
        menu();

        printf("\n请输入选项：");
        scanf("%d", &choice);

        // 处理选项
        switch(choice) {
            // === 饮品管理 ===
            case 1: add_drink(); break;
            case 2: show_drinks(); break;

            // === 订单管理 ===
            case 3: create_order(); break;
            case 4: start_order(); break;
            case 5: finish_order(); break;
            case 6: pending_orders(); break;
            // === 数据统计 ===（尚未实现）
            case 7: ; break;
            case 8: ; break;
            case 9: ; break;
            // ==原料管理与数据存储 ===
            case 11: add_material(); break;
            case 12: show_materials(); break;
            case 13: replenish_material(); break;
            case 14: query_material(); break;
            case 15: material_statistics(); break;
            case 16: check_stock_warning(); break;



            // === 退出 ===
            case 10: save_data(); break;
            case 0:
                printf("\n退出\n");
                exit(0);

            default:
                printf("无效选项，请重新输入\n");
        }

        // 暂停等待用户查看（防止用户输入错误 导致程序崩溃）
        // 两次调用getchar（）函数 读取缓冲区中的回车符
        if(choice != 0) {
            printf("\n按任意键继续...");
            getchar(); getchar();
        }
    }
    // 通过 return 0 退出程序
    return 0;
}