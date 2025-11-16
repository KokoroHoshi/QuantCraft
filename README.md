# QuantCraft - C++ 模組化回測工具

一個用 C++ 開發的模組化量化策略回測工具，提供股票數據獲取、技術指標計算、投資策略回測功能，以及 Web API 服務。

## 功能特色

### 🔍 數據擷取
- 從 Yahoo Finance API 獲取歷史股票數據
- 本地 JSON 數據存儲

### 📊 技術指標
- 簡單移動平均線 (SMA)
- 模組化架構，易於擴充新指標

### 🧠 投資策略
- 雙(均)線交叉策略 (Double Line Crossover)
- 基於技術指標生成買賣信號
- 支援可短倉位交易

### 📈 回測引擎
- 完整的投資策略回測框架
- 計算總利潤、勝率等關鍵指標
- 輸出回測結果和交易記錄至 JSON 格式

### 🌐 Web API 服務
- 基於 Drogon 框架的高效能 C++ Web 服務器
- RESTful API 提供股票數據查詢
- 運行在 8080 端口

## 專案架構

```
QuantCraft/
├── .devcontainer/      # VS Code Remote Container 配置
├── build/              # 編譯輸出目錄
├── data/               # 股票數據JSON文件
├── logs/               # 日誌文件
├── output/             # 回測輸出結果
├── src/                # 源代碼
│   ├── api/           # Web API 控制器
│   │   ├── StockController.h/cpp - API端點實作
│   ├── core/          # 核心業務邏輯
│   │   ├── Backtester.h/cpp     - 回測引擎
│   │   ├── Candlestick.h/cpp    - K線數據
│   │   ├── Indicators.h/cpp     - 技術指標
│   │   ├── Stock.h/cpp          - 股票數據模型
│   │   ├── Strategy.h           - 策略基類
│   │   └── Trade.h              - 交易記錄
│   ├── io/             # 輸入輸出模組
│   │   ├── JsonParser.h/cpp     - JSON數據解析
│   │   └── fetch_stock.cpp      - 命令行數據獲取工具
│   ├── services/       # 服務層
│   │   └── StockService.h/cpp   - 股市數據服務
│   └── strategy/       # 投資策略
│       └── DoubleLineCrossover.h/cpp - 雙均線策略
├── CMakeLists.txt      # CMake 構建配置
├── drogon_config.json  # Drogon 服務器配置
├── LICENSE             # 許可證文件
└── README.md           # 本文件
```

## 技術棧

- **程式語言**: C++17
- **Web 框架**: Drogon
- **HTTP 客户端**: cpp-httplib
- **JSON 處理**: nlohmann/json
- **建构系統**: CMake

## 快速開始

### 使用 VS Code + Remote Container（推薦）

本專案支援 VS Code Remote Container，可以在容器化環境中開發：

1. 確保已安裝 VS Code 和 "Dev Containers" 擴充功能
2. 開啟專案資料夾
3. 當提示時，點擊 "Reopen in Container"
4. 在容器中開啟終端機，執行以下命令設定和編譯專案：
   ```bash
   cmake -B build -S .
   cmake --build build
   ```

5. **啟動 Web 服務器**:
   ```bash
   ./build/main
   ```
   服務器將運行在 http://localhost:8080

6. 或執行其他工具:
   ```bash
   ./build/fetch_stock    # 獲取股票數據
   ./build/local_test     # 執行本地回測
   ```

### 本地開發環境需求

- CMake 3.28.3+
- C++17 編譯器
- vcpkg 或相似包管理器（用於安裝依賴）

### 安裝依賴

```bash
# 使用 vcpkg 安裝所需庫
vcpkg install httplib nlohmann-json drogon
```

### 編譯專案

```bash
mkdir build
cd build
cmake ..
make
```

### 運行

1. **啟動 Web 服務器**:
   ```bash
   ./main
   ```
   服務器將運行在 http://localhost:8080

2. **獲取股票數據**:
   ```bash
   ./fetch_stock
   ```

3. **執行本地回測**:
   ```bash
   ./local_test
   ```

## API 使用

### 股票數據查詢

```
GET /api/stock?symbol=0050.TW&range=1y&interval=1d
```

參數：
- `symbol`: 股票代碼（如 0050.TW）
- `range`: 數據範圍（如 1y, 2y）
- `interval`: 數據間隔（如 1d, 1wk）

### 測試端點

```
GET /test
```

返回簡單的測試訊息。

## 使用範例

### 本地策略回測

```cpp
#include "Stock.h"
#include "JsonParser.h"
#include "Indicators.h"
#include "DoubleLineCrossover.h"
#include "Backtester.h"

int main() {
    // 載入股票數據
    Stock stock("0050", Parser::parseYfinanceJsonFile("data/0050.TW_1y_1d.json"));

    // 計算技術指標
    auto fast_MA = Indicators::SMA(stock.candles, 5);
    auto slow_MA = Indicators::SMA(stock.candles, 10);

    // 設置策略
    DoubleLineCrossover strategy(fast_MA, slow_MA);

    // 執行回測
    Backtester backtester(stock, &strategy, true);  // 允許做空
    backtester.run();

    // 打印績效
    backtester.printPerformance();

    return 0;
}
```

## 開發與擴充

### 添加新指標
1. 在 `Indicators.h/cpp` 中實作新指標函數
2. 在 `DoubleLineCrossover` 或新建策略類中使用

### 添加新策略
1. 繼承 `Strategy` 類
2. 實作 `generateSignals()` 方法
3. 返回買賣信號向量

### 添加新 API 端點
1. 在 `StockController` 中添加新方法
2. 更新 `METHOD_LIST_BEGIN/END` 區塊

## 許可證

本專案釋出於 MIT 許可證下。

## 貢獻

歡迎提交 Issues 和 Pull Requests。

---

**注意**: 此專案僅供教育和研究使用，請勿用於實際投資決策。
