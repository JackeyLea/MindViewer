import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import com.onecurve 1.0
import "./"

Window {
    //flags: Qt.FramelessWindowHint

    id: mindviewerID

    x: 0
    y: 0
    width: 1080
    height: 900
    visible: true
    //color: "#000000ff"
    color: "white"
    //maximumHeight: 720
    //maximumWidth: 1080
    minimumHeight: 720
    minimumWidth: 1080
    modality: Qt.WindowModal
    visibility: Window.AutomaticVisibility
    title: qsTr("MindViewer")

    Rectangle {
        id: rectRaw

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 10
        width: 500
        height: 100

        OneCurve {
            id: rawCurve

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
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                rawCurve.appendPoint(value);
            }
        }

    }

    Rectangle {
        id: rectDelta

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 120
        width: 500
        height: 100

        OneCurve {
            id: deltaCurve

            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(1, 0.5, 0, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                deltaCurve.appendPoint(value);
            }
        }

    }

    Rectangle {
        id: rectTheta

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 230
        width: 500
        height: 100

        OneCurve {
            id: thetaCurve

            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(1, 1, 0, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                thetaCurve.appendPoint(value);
            }
        }

    }

    Rectangle {
        id: rectLowAlpha

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 340
        width: 500
        height: 100

        OneCurve {
            id: lowAlphaCurve

            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(0, 1, 0, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                lowAlphaCurve.appendPoint(value);
            }
        }

    }

    Rectangle {
        id: rectHighAlpha

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 450
        width: 500
        height: 100

        OneCurve {
            id: highAlphaCurve

            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(0, 1, 1, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                highAlphaCurve.appendPoint(value);
            }
        }

    }

    Rectangle {
        id: rectLowBeta

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 450
        width: 500
        height: 100

        OneCurve {
            id: lowBetaCurve

            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(0, 1, 1, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                lowBetaCurve.appendPoint(value);
            }
        }

    }

    Rectangle {
        id: rectHighBeta

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 560
        width: 500
        height: 100

        OneCurve {
            id: highBetaCurve

            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(0, 0, 1, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                highBetaCurve.appendPoint(value);
            }
        }

    }

    Rectangle {
        id: rectLowGarmma

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 670
        width: 500
        height: 100

        OneCurve {
            id: lowGarmmaCurve

            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(0.5, 0, 0.5, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                lowGarmmaCurve.appendPoint(value);
            }
        }

    }

    Rectangle {
        id: rectMidGarmma

        color: Qt.rgba(0, 0, 1, 0.1)
        //anchors.fill: parent
        anchors.margins: 10
        radius: 5
        x: 10
        y: 780
        width: 500
        height: 100

        OneCurve {
            id: midGarmmaCurve

            pointCount: 800
            spaceCount: 5
            anchors.fill: parent
            yMax: 8000
            yMin: 0
            lineWidth: 2
            lineColor: Qt.rgba(0.5, 0.5, 0.5, 1)
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property int current: 0
            property var valueList: [2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 4950, 4960, 4970, 4980, 4990, 5000, 4990, 4980, 4970, 4960, 4950, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4000, 3900, 3800, 3700, 3600, 3500, 3400, 3300, 3200, 3100, 3000, 2900, 2800, 2700, 2600, 2500, 2400, 2300, 2200, 2100]

            running: true
            interval: 1
            repeat: true
            onTriggered: {
                var value = valueList[current];
                current = current + 1;
                if (current >= valueList.length)
                    current = 0;

                midGarmmaCurve.appendPoint(value);
            }
        }

    }

    Item {
        id: wifiItem

        //color: Qt.rgba(0, 0, 1, 0.1)
        anchors.top: parent.top
        anchors.right: batteryRectID.left
        anchors.margins: 10
        //radius: 5
        width: 70
        height: 50

        WIFI {
            //anchors.top: parent.top
            //anchors.right: parent.right
            // PropertyAnimation {         //电量变动动画
            //     id:batterChange
            //     target: batteryID
            //     property: "batteryLevel"
            //     duration: 500
            //     easing.type: Easing.InOutQuad
            // }

            id: wifiID
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property double current: 0

            running: true
            interval: 100
            repeat: true
            onTriggered: {
                current = current + 1;
                if (current > 5)
                    current = 0;

                wifiID.wifiLevel = current;
            }
        }

    }

    Item {
        id: batteryRectID

        //color: Qt.rgba(0, 0, 1, 0.1)
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        //radius: 5
        width: 100
        height: 50

        Battery {
            //anchors.top: parent.top
            //anchors.right: parent.right
            // PropertyAnimation {         //电量变动动画
            //     id:batterChange
            //     target: batteryID
            //     property: "batteryLevel"
            //     duration: 500
            //     easing.type: Easing.InOutQuad
            // }

            id: batteryID
        }

        // FIXME 2021-08-07 : timer for test
        Timer {
            property double current: 0

            running: true
            interval: 100
            repeat: true
            onTriggered: {
                current = current + 0.01;
                if (current >= 1)
                    current = 0;

                batteryID.batteryLevel = current;
            }
        }

    }

    Dial {
        id: meditationDial

        x: 600
        y: 10
        width: 300
        height: 300
    }

    Dial {
        id: attentionDial

        x: 600
        y: 400
        width: 300
        height: 300
    }

    RowLayout {
        x: 550
        y: 800
        spacing: 10

        Button {
            // TODO 打开并读取文件

            id: btnOpen

            Layout.fillWidth: true
            Layout.minimumWidth: 64
            Layout.preferredWidth: 64
            Layout.maximumWidth: 64
            Layout.minimumHeight: 64
            onClicked: {
            }

            Image {
                id: backgroundOpenImage

                source: "qrc:/resources/icons/open.svg" // 替换为您的图片路径
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
            }

        }

        Button {
            id: btnExit

            Layout.fillWidth: true
            Layout.minimumWidth: 64
            Layout.preferredWidth: 64
            Layout.maximumWidth: 64
            Layout.minimumHeight: 64
            onClicked: {
                Qt.quit();
            }

            Image {
                id: backgroundExitImage

                source: "qrc:/resources/icons/exit.svg" // 替换为您的图片路径
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
            }

        }

    }

}
