import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: header_controls
    property bool appednable: true
    Button{
        id: add_button
        text: "Загрузить записи"
        width: parent.width*0.5
        height: parent.height
        anchors{
            top: parent.top
            left: parent.left
        }
        onClicked: {
            entries_manager.load()
        }
    }
}
