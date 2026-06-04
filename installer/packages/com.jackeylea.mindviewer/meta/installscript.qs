function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        // 创建开始菜单快捷方式
        component.addOperation("CreateShortcut",
            "@TargetDir@/MindViewer.exe",
            "@StartMenuDir@/MindViewer.lnk",
            "workingDirectory=@TargetDir@",
            "iconPath=@TargetDir@/MindViewer.exe",
            "description=MindViewer - TGAM脑波模块图像化显示工具");

        // 创建桌面快捷方式
        component.addOperation("CreateShortcut",
            "@TargetDir@/MindViewer.exe",
            "@DesktopDir@/MindViewer.lnk",
            "workingDirectory=@TargetDir@",
            "iconPath=@TargetDir@/MindViewer.exe",
            "description=MindViewer - TGAM脑波模块图像化显示工具");
    }
}
