find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS LinguistTools)
# 添加翻译文件
list(APPEND TRANSLATIONS en_US.ts zh_CN.ts)

# 使用 Qt6 的 LinguistTools 自动处理翻译文件
qt6_add_translations(winAutoShutdown TS_FILES ${TRANSLATIONS}
        RESOURCE_PREFIX "/language"
)
