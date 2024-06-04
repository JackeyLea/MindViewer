// Battery.qml

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Rectangle {
    id:root
    property real batteryLevel: 1
    property real borderWidth: 3
    property color borderColor: "#aaaaaa"
    property color nomalLevelColor: "#4CAF50"
    property color lowLevelColor: "#FFC107"
    property color lowerLevelColor: "red"

    width: 100
    height: 50
    color: Qt.rgba(0, 0, 1, 0.1)

    // 电池体
    Rectangle {
        id: batteryContainer
        width: parent.width - 2 * borderWidth
        height: parent.height - 2 * borderWidth
        anchors.centerIn: parent
        color: borderColor
        border.color: borderColor // 设置边界线颜色
        border.width: borderWidth // 设置边界线宽度
        radius:10
        // 电量rect
        Rectangle {
            id:colorRectiud
            width: (batteryContainer.width - 2 * borderWidth)*(batteryLevel)
            height: batteryContainer.height - 2 * borderWidth
            anchors.verticalCenter: parent.verticalCenter
            x: borderWidth
            color: colorBasedOnValue(batteryLevel)
            radius:5
            // 电量颜色获取函数
            function colorBasedOnValue(value) {
                if (value < 0.1) {
                    return root.lowerLevelColor;
                } else if (value < 0.2) {
                    return root.lowLevelColor;
                } else {
                    return root.nomalLevelColor; // 默认值或其他颜色
                }
            }
        }
        // 电量文字
        Text {
            anchors.centerIn: parent
            text: Math.floor(batteryLevel * 100) + "%"
            font.pixelSize: 20
            color: "white"
        }
    }
    //电池头
    Rectangle {
        id: batteryHeader
        width: batteryContainer.width / 18
        height: batteryContainer.height / 2.5
        anchors.left:batteryContainer.right
        anchors.verticalCenter: batteryContainer.verticalCenter
        color: borderColor
        radius: 5
        Rectangle {
            x: 0
            y: 0
            width: parent.radius
            height: parent.height
            radius: 0
            color: parent.color
        }
    }
}
