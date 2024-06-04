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
    /*Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 1080
        height: 720
        color: "#ff0000"

        ColumnLayout {
            id: columnLayout
            y: 10
            width: 500
            height: 500

            Rectangle {
                id: rectRaw
                width: 500
                height: 100
                color: "#ffffff"
            }

            Rectangle {
                id: rectAlpha
                width: 500
                height: 100
                color: "#ffffff"
            }

            Rectangle {
                id: rectBeta
                width: 500
                height: 100
                color: "#ffffff"
            }

            Rectangle {
                id: rectDelta
                width: 500
                height: 100
                color: "#ffffff"
            }

            Rectangle {
                id: rectGarmma
                width: 500
                height: 100
                color: "#ffffff"
            }

            Rectangle {
                id: rectThelta
                width: 500
                height: 100
                color: "#ffffff"
            }
        }
    }*/
}
