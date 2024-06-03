import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml 2.15
import QtQuick.Shapes 1.15

Window {
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
        id: rectangle
        x: 0
        y: 0
        width: 1080
        height: 720
        color: "#ff0000"

        ColumnLayout {
            id: columnLayout
            y: 10
            width: 100
            height: 100

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
    }
}
