import QtQuick 2.6
import QTendencyChart 1.0

Rectangle {
    //property alias mouseArea: mouseArea
    //property alias textEdit: textEdit

    width: 360
    height: 360

    QTendencyChart {
        id: mouseArea
        anchors.fill: parent
    }

//    TextEdit {
//        id: textEdit
//        text: qsTr("Enter some text...")
//        verticalAlignment: Text.AlignVCenter
//        anchors.top: parent.top
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.topMargin: 20
//        Rectangle {
//            anchors.fill: parent
//            anchors.margins: -10
//            color: "transparent"
//            border.width: 1
//        }
//    }
}
