import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import com.onecurve 1.0
import "./"

Window {
    id:mindviewerID
    x: 0
    y: 0
    width: 1080
    height: 720
    visible: true
    color: "#000000ff"
    maximumHeight: 720
    maximumWidth: 1080
    minimumHeight: 720
    minimumWidth: 1080
    modality: Qt.WindowModal
    visibility: Window.AutomaticVisibility
    title: qsTr("MindViewer")

    Rectangle {
        color: Qt.rgba(0, 0, 1, 0.1)
        anchors.fill: parent
        anchors.margins: 10
        radius: 5

        OneCurve {
            id: paintItem
            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(1, 0, 0, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            running: true
            interval: 1
            repeat: true

            property int current: 0
            property var valueList: [
                2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900,
                3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900,
                4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900,
                4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950,
                4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000,
                3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000,
                2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100,
            ]

            onTriggered: {
                var value = valueList[current]
                current = current + 1
                if (current >= valueList.length) {
                    current = 0
                }

                paintItem.appendPoint(value)
            }
        }
    }

    Rectangle{
        color: Qt.rgba(0, 0, 1, 0.1)
        anchors.top: parent.top
        anchors.right: batteryRectID.left
        anchors.margins: 10
        radius: 5
        width: 70
        height: 50

        WIFI {
            id: wifiID
            //anchors.top: parent.top
            //anchors.right: parent.right

            // PropertyAnimation {         //电量变动动画
            //     id:batterChange
            //     target: batteryID
            //     property: "batteryLevel"
            //     duration: 500
            //     easing.type: Easing.InOutQuad
            // }
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            running: true
            interval: 100
            repeat: true

            property double current: 0

            onTriggered: {
                current = current + 1
                if (current > 5) {
                    current = 0
                }

                wifiID.wifiLevel = current
            }
        }
    }

    Rectangle{
        id: batteryRectID
        color: Qt.rgba(0, 0, 1, 0.1)
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        radius: 5
        width:100
        height:50

        Battery {
            id:batteryID
            //anchors.top: parent.top
            //anchors.right: parent.right

            // PropertyAnimation {         //电量变动动画
            //     id:batterChange
            //     target: batteryID
            //     property: "batteryLevel"
            //     duration: 500
            //     easing.type: Easing.InOutQuad
            // }
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            running: true
            interval: 100
            repeat: true

            property double current: 0

            onTriggered: {
                current = current + 0.01
                if (current >= 1) {
                    current = 0
                }

                batteryID.batteryLevel = current
            }
        }
    }

    Dial {
        property int svalue:0

        id: speed_car
        x: 175
        y: 93
        width: 291
        height: 238
        dial_addR: -6
        dial_longNum: 10
        dial_longLen: 15
        dial_lineWidth: 3
        btm_lineWidth: 22
        top_lineWidth: 10
        top_endAngle: svalue*1.3+140
        top_startAngle: 140
        btm_endAngle: 400
        btm_startAngle: 140
        btm_r: 120
        top_r: 120

        Text {
            id: speed
            x: 104
            y: 116
            width: 89
            height: 44
            text: parent.svalue
            style: Text.Normal
            font.weight: Font.ExtraBold
            font.capitalization: Font.MixedCase
            font.pixelSize: 40
            font.bold: true
            font.family: "Verdana"
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: speed_label
            x: 120
            y: 154
            width: 45
            height: 30
            text: qsTr("冥想值")
            font.pointSize: 11
            font.bold: true
            verticalAlignment: Text.AlignBottom
        }

        Label {
            id: label2
            x: 263
            y: 235
            width: 33
            height: 25
            text: qsTr("200")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label4
            x: 300
            y: 180
            width: 42
            height: 25
            text: qsTr("180")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label6
            x: 310
            y: 100
            width: 23
            height: 25
            text: qsTr("160")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label8
            x: 270
            y: 30
            width: 35
            height: 25
            text: qsTr("140")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label10
            x: 200
            y: -20
            width: 36
            height: 25
            text: qsTr("120")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label11
            x: 130
            y: -30
            width: 23
            height: 25
            text: qsTr("100")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label9
            x: 60
            y: -20
            width: 23
            height: 25
            text: qsTr("80")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label7
            x: 0
            y: 30
            width: 23
            height: 25
            text: qsTr("60")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label5
            x: -30
            y: 102
            width: 23
            height: 25
            text: qsTr("40")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label3
            x: -28
            y: 172
            width: 23
            height: 25
            text: qsTr("20")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label1
            x: 8
            y: 235
            width: 23
            height: 25
            text: qsTr("0")
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
        }
    }

    // FIXME 2021-08-07 : timer for test
    Timer {
        running: true
        interval: 1000
        repeat: true

        property int current: 0

        onTriggered: {
            current = current + 10
            if (current >= 200) {
                current = 0
            }

            if(current<60) {
                speed.color = "red"
            }
            else if(current<120) {
                speed.color = "#f2ac28"
            }
            else {
                speed.color = "green"
            }
            speed_label.color = speed.color
            speed_car.svalue=current
        }
    }
}
