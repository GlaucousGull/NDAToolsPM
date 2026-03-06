#include "inputvalidator.h"

// 作用：实现 InputValidator 的各类输入校验逻辑，返回统一的 ValidationResult
// 范围：IP/端口/主机名/网络地址/文件路径/字符串非空与长度/数值范围/Hex/Base64

#include <QFileInfo>    // 包含Qt文件信息类，用于检查文件路径是否存在及是否为常规文件
#include <QUrl>         // 包含QT URL类（当前为直接使用，可能为未来预留扩展）

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

// 定义并初始化 IPv4 地址正则表达式的静态常量成员
// 用于检查一个字符串是否为有效的IPv4地址（192.168.1.1）
const QRegularExpression InputValidator::ipv4Regex(
    R"(^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)"
    );

// 定义并初始化 IPv6 地址正则表达式的静态常量成员
// 检查一个字符串是否为有效的IPv4地址（工业级）
const QRegularExpression InputValidator::ipv6Regex(
    R"(^(?:(?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}|"
    R"(::(?:[0-9a-fA-F]{1,4}:){0,6}[0-9a-fA-F]{1,4}|"
    R"( [0-9a-fA-F]{1,4}::(?:[0-9a-fA-F]{1,4}:){0,5}[0-9a-fA-F]{1,4}|"
    R"( [0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}::(?:[0-9a-fA-F]{1,4}:){0,4}[0-9a-fA-F]{1,4}|"
    R"( [0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}::(?:[0-9a-fA-F]{1,4}:){0,3}[0-9a-fA-F]{1,4}|"
    R"( [0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}::(?:[0-9a-fA-F]{1,4}:){0,2}[0-9a-fA-F]{1,4}|"
    R"( [0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}::(?:[0-9a-fA-F]{1,4}:)?[0-9a-fA-F]{1,4}|"
    R"( [0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}::[0-9a-fA-F]{1,4}|"
    R"( [0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}:[0-9a-fA-F]{1,4}::))$)"
    );

// 定义并初始化主机名正则表达式的静态常量成员
// 检查一个字符串是否为有效的主机名称或域名（比如：www.baidu.com
const QRegularExpression InputValidator::hostnameRegex(
    R"(^(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*)$)"
    );

// 定义并十六进制字符串正则表达式的静态常量成员
const QRegularExpression InputValidator::hexRegex(
    R"(^[0-9a-fA-F]+$)"
    );

// 定义并初始化Base64正则表达式正则表达式的静态常量成员
const QRegularExpression InputValidator::base64Regex(
    R"(^[a-zA-Z0-9+/]*={0,2}$)"
    );

// IP地址校验函数：验证输入的字符串是否为有效的IPv4或IPv6地址
InputValidator::ValidationResult InputValidator::validatorIPAddress(const QString& ipAddress)
{
    // 判断字符串是否为空
    if(ipAddress.isEmpty()) {
        return ValidationResult(false, "IP地址不能为空");
    }

    // 使用Qt的QHostAddress类尝试解析IP地址
    QHostAddress address(ipAddress);
    if(address.isNull()) {
        return ValidationResult(false, "IP地址格式无效");
    }

    // 验证解析出的地址协议类型是否为：IPv4 IPv6
    if(address.protocol() != QAbstractSocket::IPv4Protocol
        && address.protocol() != QAbstractSocket::IPv6Protocol) {
        return ValidationResult(false, "不支持的IP地址类型");
    }

    return ValidationResult(true);
}

// 端口校验函数：验证整数端口号是否在有效范围内
InputValidator::ValidationResult InputValidator::validatorPort(int port)
{
    if(port < 1 || port > 65535) {
        return ValidationResult(false, "端口号无效,端口号必须在[1, 65535]内");
    }
    return ValidationResult(true);
}

// 端口字符串校验函数：将字符串转换为整数后调用数值校验
InputValidator::ValidationResult InputValidator::validatorPort(const QString& portStr)
{
    if(portStr.isEmpty()) {
        return ValidationResult(false, "端口不能为空");
    }

    bool flag = false;
    int port = portStr.toInt(&flag);
    if(!flag) {
        return ValidationResult(false, "端口号不能包含非数字");
    }
    return validatorPort(port);
}

// 主机名校验函数：验证输入是否符合FRC标准的主机名格式
InputValidator::ValidationResult InputValidator::validatorHostname(const QString& hostname)
{
    // 第一层检查：判断输入字符串是否为空
    if(hostname.isEmpty()) {
        ValidationResult(false, "主机名不能为空");
    }

    // 第二层检查：验证主机名总长度是否符合RFC标准（最大253字节）
    if(hostname.length() > 253) {
        return ValidationResult(false, "主机名称长度不能超过253字节");
    }

    // 第三层检查：使用预编译的正则表达式验证主机名的字符格式
    if(!hostnameRegex.match(hostname).hasMatch()) {
        return ValidationResult(false, "主机名格式无效");
    }

    return ValidationResult(true);
}

// 网络地址校验函数：尝试按IP地址校验，失败则按主机名校验
InputValidator::ValidationResult InputValidator::validatorNetworkAddress(const QString& address)
{
    // 判空
    if(address.isEmpty()) {
        return ValidationResult(false, "网络地址不能为空");
    }

    // 优先尝试按IP地址格式进行校验
    ValidationResult ipResult = validatorIPAddress(address);
    if(ipResult.isValid) {
        return ipResult;
    }

    // IP校验失败后，尝试按主机名格式进行检查
    ValidationResult hostnameResult = validatorHostname(address);
    if(hostnameResult.isValid) {
        return hostnameResult;
    }
    return ValidationResult(false, "网络地址不能为空");
}

// 文件路径校验函数：验证文件路径格式，可选检查文件是否存在
InputValidator::ValidationResult InputValidator::validatorFilePath(const QString& filePath, bool mustExist)
{
    // 判断输入文件路径字符串是否为空
    if(filePath.isEmpty()) {
        return ValidationResult(false, "文件路径不能为空");
    }
    // 创建QfileInfo对象用于文件信息查询
    QFileInfo fileInfo(filePath);

    // 如果要求文件必须存在，则检查文件是否存在
    if(mustExist && !fileInfo.exists()) {
        return ValidationResult(false, "指定的文件不存在");
    }

    // 如果要求文件必须存在，则检查路径否为常规文件（非目录或特殊文件）
    if(mustExist && !fileInfo.isFile()) {
        return ValidationResult(false, "指定的路径不是文件");
    }

    return ValidationResult(true);
}

// 非空字符串校验函数：验证字符串不为空且不仅包含空白字符
InputValidator::ValidationResult InputValidator::validatorNonEmptyString(const QString& str, const QString& fieldName)
{
    // 判断字符串是否为空（长度为0）
    if(str.isEmpty()) {
        return ValidationResult(false, QString("%1不能为空").arg(fieldName));
    }

    // 判断掉首位空白字符后是否为空（防止仅输入空格、制表符等)
    if(str.trimmed().isEmpty()) {
        return ValidationResult(false, QString("%1不能只包含空白字符").arg(fieldName));
    }
    return ValidationResult(true);
}

// 字符串长度区间校验函数：验证字符串长度是否在指定范围内（闭区间）
InputValidator::ValidationResult InputValidator::validatorStringLength(const QString& str, int minLength, int maxLength, const QString& fieldName)
{
    // 获取输入字符串的长度
    int length = str.length();

    // 判断字符串长度是否小于最小值
    if(length < minLength) {
        return ValidationResult(false, QString("%1字符长度不能小于%2个字符").arg(fieldName, minLength));
    }

    // 判读字符串长度是否大于最大值
    if(length > maxLength) {
        return ValidationResult(false, QString("%1长度不能大于%2个字符").arg(fieldName, maxLength));
    }
    return ValidationResult(true);
}

// 数值范围校验函数：验证函数是否在指定范围内（闭区间）
InputValidator::ValidationResult InputValidator::validatorNumberRange(int value, int minValue, int maxValue, const QString& fieldName)
{
    // 判断数值是否小于最小值
    if(value < minValue) {
        return ValidationResult(false, QString("%1字符长度不能小于%2个字符").arg(fieldName, minValue));
    }

    // 判断数值是否大于最大值
    if(value > maxValue) {
        return ValidationResult(false, QString("%1长度不能大于%2个字符").arg(fieldName, maxValue));
    }
    return ValidationResult(true);
}

// 十六机制字符串校验函数：验证字符串是否为有效的十六机制格式
InputValidator::ValidationResult InputValidator::validatorHexString(const QString& hexStr)
{
    // 判断输入字符串是否为空
    if(hexStr.isEmpty()) {
        return ValidationResult(false, "十六进制字符串不能为空");
    }

    // 直接使用预编译的正则表达式验证字符串是否只包含有效的十六机制字符
    if(!hexRegex.match(hexStr).hasMatch()) {
        return ValidationResult(false, "十六进制字符串智能包含 0-9 a-f A-F");
    }

    // 验证字符串长度是否为偶数（每个字节需要2个十六进制字符表示，确保字符对齐）
    if(hexStr.length() % 2 != 0) {
        return ValidationResult(false, "十六进制字符串长度必须是偶数");
    }
    return ValidationResult(true);
}

// Base64字符串校验函数：验证字符串是否符合Base64编码格式
InputValidator::ValidationResult InputValidator::validatorBase64String(const QString& base64str)
{
    // 判空
    if(base64str.isEmpty()) {
        return ValidationResult(false, "Base64字符串不能为空");
    }

    // 使用预编译正则表示验证字符串是否只包含有效Base64字符
    if(!base64Regex.match(base64str).hasMatch()) {
        return ValidationResult(false, "Base64字符串格式无效");
    }

    // 验证字符串长度是否为4的背书（Base64编码规则：每3个字节原始数据编码为4个Base64字符）
    if(base64str.length() % 4 != 0) {
        return ValidationResult(false, "Base64字符串长度必须是4的倍数");
    }

    return ValidationResult(true);
}
