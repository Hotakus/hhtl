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

## 测试

对哈希表的性能进行测试。默认的测试数量是10000000。  
* System: Windows 11 64bits
* Memory: 16 GiB
* CPU   : Intel I7-8700

### 负载因子
我们知道，哈希表中有负载因子，其计算公式为：Load factor = Occupation / Capacity  
其中：`Load factor`即负载因子， `Occupation` 即哈希表实际数据量，
`Capacity` 即哈希表所分配容量。  
当负载因子为 1 时，代表哈希表被“存满了”（实际可能没有，因为存在哈希冲突），这个时候一般需要进行 rehash（再散列）。  
再散列即对原哈希表进行备份、扩容、用哈希函数在新尺度下再哈希化。rehash可以将原本紧凑的数据分散开来，保证数据存取的效率。

### 冲突比
冲突比即 CRatio = Collision / Capacity  
其中，`CRatio即冲突比`，`Collision` 即冲突数量，`Capacity` 即哈希表所分配容量。  
冲突比表示：当前哈希表被浪费的空间。例如当负载因子为 1 时，哈希表容量为100，冲突数据量为20，那么
就代表哈希表有20的空间被浪费了，两者之比即冲突比。冲突比越低即哈希表空间利用率越高，数据分布更均匀。  

该哈希库使用链式方法处理冲突。当哈希负载因子为 1 ，数据量10000000时，最长冲突链表平均可以维持在10以下，
即存取时间复杂度在负载因子为1时平均最坏为 O(1 + 10 / 2)。

### 开始测试

在该哈希库中，存在两个常数值：
- `HASH_TABLE_COLLISION_MAX_RADIO` （哈希表最大冲突比）
- `HASH_TABLE_HIGHEST_PERFORMANCE_MULTIPLE`（哈希表最高性能倍数）


**哈希表最高性能倍数：** 即该库 “哈希表的容量” 为 “实际数据量” 的 `HASH_TABLE_HIGHEST_PERFORMANCE_MULTIPLE` 倍时，达到最高性能，
此时的负载因子为 `1 / 哈希表最高性能倍数`。  
**哈希表最大冲突比：** 根据该哈希表库的哈希函数所测试得来的一个常数值，主要用于判断当前
哈希表是否需要 rehash。

测试将围绕 `哈希表最高性能倍数` 进行。测试负载因子为 1 时，与负载因子
为 `1 / 哈希表最高性能倍数` 时的哈希表性能差距。


测试数据量 `tc` 为10000000，其中，程序随机产生 10000000 keys，对keys进行增查操作。
下面是一段负载因子为 1 时的测试例子：

```commandline
Number of tests: 10000000
Initializing...
Create    elapsed time: 0 secs, 0 ms, 12 us
Put       elapsed time: 3 secs, 3965 ms, 3965912 us
Max       collision chain length: 8 
SingleGet elapsed time: 0 secs, 0 ms, 0 us (biqvpxcxct : 114514 - true)
Get       elapsed time: 3 secs, 3077 ms, 3077344 us
Collision count: 3678676, valid size: 10000000 (space utilization: 63.21%)
Destro    elapsed time: 1 secs, 1872 ms, 1872798 us
Free      elapsed time: 0 secs, 438 ms, 438566 us
Total     elapsed time: 9 secs, 9417 ms, 9417415 us
```
其中：
* `Create` 代表创建哈希表耗时，一般较为稳定。
* `Put` 代表哈希表进行 `tc` 次 Put 操作，耗时为 3965 ms。
* `Max collision chain length` 代表负载因子为1，数据量为`tc`时的最长冲突链表长度
* `Single Get` 代表单次 Get 耗时
* `Get` 代表哈希表进行 `tc` 次 `Get` 操作，耗时 3077 ms。
* `Collision count` 代表负载因子为 1，数据量为 `tc` 时的冲突数据量，括号内为空间利用率
* `Destro` 代表销毁哈希表耗时。
* `Free` 代表 `tc` 个 Keys 释放耗时。
* `Total` 表示总耗时。

<br>

对此，在单次运行时，进行数据量为 `tc` ，连续 5 次的测试取平均值：  
`Put: (3993 + 3938 + 4035 + 4024 + 4118) / 5 = 4021 ms`，标准差：65.73  
`Get: (3010 + 3054 + 3028 + 2963 + 3015) / 5 = 3014 ms`，标准差：33.22  
平均空间利用率（未冲突数据量 / 数据总量）：63.20%


同样的，当负载因子为 `1 / 哈希表最高性能倍数` 时并在单次运行时，进行数据量为 `tc` ，连续 5 次的测试取平均值：  
`Put: (3199 + 3132 + 3145 + 3144 + 3133) / 5 = 3150 ms`，标准差：27.72  
`Get: (2324 + 2385 + 2338 + 2326 + 2353) / 5 = 2345 ms`，标准差：25.07  
平均空间利用率（未冲突数据量 / 数据总量）：87.78%

### 结果
可以看到，当负载因子（α）为 1 时 与 负载因子 为 `1 / 哈希表最高性能倍数` 时
的测试数据有明显差异。  
当 `α == 1` 时，Put 的平均耗时比 `α == (1 / 哈希表最高性能倍数)` 时
要多 871 ms，Get 的平均耗时要多 669 ms，平均空间利用率相差 24.58%

从标准差看，当 `α == 1` 时，Put 和 Get 更不稳定，空间利用率更低。

此外，若进一步增加 `哈希表最高性能倍数` 的数值，哈希表性能反而会呈下降趋势。

---

## TODO
- [ ] 设计增量再散列（Incremental Rehashing）提高再散列效率。

---
