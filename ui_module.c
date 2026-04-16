//
// Created by H on 2026/3/10.
//
#include "include Milktea House Management.h"

//显示主菜单
void menu() {
    // 设置控制台输出代码页为 UTF-8
    SetConsoleOutputCP(936);

   printf("\n");
   printf("        奶茶店订单管理系统\n\n");
   printf("  商品管理\n");
   printf("    1. 添加商品   2. 查看商品\n\n");
   printf("  订单管理\n");
   printf("    3. 添加订单    4. 开始制作订单\n");
   printf("    5. 保存订单    6. 加载订单\n\n");

    printf("  原料管理\n");
   printf("  11. 添加原料   12. 查看原料\n");
   printf("   13. 原料采购  14. 查询原料\n");
   printf("   15. 原料统计   16. 原料预警\n\n");
   printf("  系统退出\n");
   printf("  10. 保存退出    0. 退出系统\n");
}

