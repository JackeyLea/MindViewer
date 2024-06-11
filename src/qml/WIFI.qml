// WIFI.qml

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Rectangle {
    id:root
    property real borderWidth: 3
    property color borderColor: "#aaaaaa"
    property color nomalLevelColor: "#4CAF50"
    property color lowLevelColor: "#FFC107"
    property color lowerLevelColor: "red"
    property int wifiLevel:5 //竖线数量
    property int lineSpacing:10 //竖线间间距
    property int lineThickness: 4//竖线宽度

    width: 70
    height: 50
    color: Qt.rgba(0, 0, 1, 0.1)
    radius: 5

    //信号主体
    Repeater{
        model:wifiLevel

        Rectangle{
            x:(index * (lineThickness + lineSpacing)) + (lineThickness / 2)
            y:parent.height * ((5-index)/5)
            width:lineThickness
            height:parent.height - parent.height*((5-index)/5)
            color: "blue"
        }
    }
}
