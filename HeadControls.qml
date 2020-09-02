import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: header_controls
    property bool appednable: true
    Item{
        id: load_part
        width: parent.width*0.5
        height: parent.height*0.45
        anchors{
            top: parent.top
            left: parent.left
            leftMargin: parent.width*0.05
        }
        Button{
            id: load_button
            anchors{
                left: parent.left
                top:parent.top
            }
            height: parent.height
            width: parent.width*0.5
            text: "Загрузить записи"
            onClicked: {
                entries_manager.load(load_type.action_type)
                load_type.refresh()
            }
        }
        ActionMenu{
            id: load_type
            anchors{
                left: load_button.right
                top: parent.top
            }
            width: parent.width*0.5
            height: parent.height
        }
    }
    Item{
        id: change_part
        width: parent.width*0.5
        height: parent.height*0.45
        anchors{
            top: load_part.bottom
            left: parent.left
            topMargin: parent.height*0.05
            leftMargin: parent.width*0.05
        }
        Button{
            id: change_button
            anchors{
                left: parent.left
                top: parent.top
            }
            width: parent.width*0.5
            height: parent.height
            text: "Перегнать для изменения"
            onClicked: {
                entries_manager.change(change_type.action_type)
                change_type.refresh()
            }
        }
        ActionMenu{
            id: change_type
            anchors{
                left: change_button.right
                top: parent.top
            }
            width: parent.width*0.5
            height: parent.height
        }
   }
}
