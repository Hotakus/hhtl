# HHash table lite 

<img data-align="center" src="HHash-Table-Lite.png">

An implementation of hash table by C language, which lightweight, high-performance, and easy to use.

使用C语言实现的轻量、高效、易用的哈希表库。

---

## 如何使用

很简单，使用`git`命令，将该库下载到你的项目根目录，
```commandline
git clone https://github.com/Hotakus/hhtl.git
```
然后在你项目的`CMakeLists.txt`文件中（不是该项目）添加：
```cmake
add_subdirectory(./hhtl/)  # 添加子目录，cmake会自动编译
add_executable(your_project_name ${SRC})  # 你的可执行文件
target_link_libraries(your_project_name hhtl)  # 链接hhtl库到你的项目
```
好了，现在你可以在项目中调用hhtl了，下面是一个简单使用的例程：
```c
#include <stdio.h>
#include "./hhtl/hhtl.h"  // 导入头文件

int main() {
    // 显示库信息
    hhtl_info_show();
    
    // 创建一个哈希表对象，对象名为“hash_table_01”，预分配size为1000。
    int ps = 1000;
    hash_table_t *ht = hash_table_create("hash_table_01", ps);
    ht->set_auto_rehash(ht, true); // 设置是否自动再散列
    ht->set_rehash_method(ht, HASH_TABLE_REHASH_COLLISION);  // 再散列触发方式，默认方式为 冲突比触发
    printf("%s created successfully.\n", ht->desc);

    // 放置键值对
    char *key = "hello_01";
    int val = 114514;
    ht->put(ht, key, &val);
    printf("Put -- key: %s, value: %d\n", key, val);

    // 获取键值对
    ht_key_value_t *pair = NULL;
    pair = ht->get(ht, "hello_01");
    if (pair)
        printf("Get -- key: %s, value: %d\n", pair->name, *(int*)pair->data);
    else {
        printf("Get -- key: %s, failed.\n", key);
        return;
    }

    // 删除键值对
    ht->remove(ht, key);
    printf("Remove -- key: %s\n", key);

    // 主动再散列，再散列数值为原size的最佳性能倍数
    ht->rehash(ht, (int)((float)ps * HASH_TABLE_HIGHEST_PERFORMANCE_MULTIPLE));
    printf("Rehash\n");

    // 销毁哈希表
    hash_table_destroy(ht);
    printf("Destroy\n");
    
    return 0;
}
```
当然，你可以在`config.h`文件中修改`HHTL_TEST`的值为 1，然后
调用`hash_test()`函数进行Hash表系统的测试，这会比较耗内存:
```c
#include "./hhtl/hhtl.h"
int main() {
    hash_test();      // 哈希表系统测试
    // hash_example;  // 哈希表简单测试
    return 0;
}
```
测试完后记得将`HHTL_TEST`的值修改为 0 关闭测试。

---

## Test



---
