import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Pacman")
    color: "grey"

    Item {
        anchors.fill: parent

        Column {
            anchors.centerIn: parent
            spacing: 20
            width: 200
            Button {
                width: parent.width
                text: "Play"
            }
            Button {
                width: parent.width
                text: "Replay"
            }
            Button {
                width: parent.width
                text: "Quit"
            }
        }
    }
}
