import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "./"

Rectangle{
    DialBackground {
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
