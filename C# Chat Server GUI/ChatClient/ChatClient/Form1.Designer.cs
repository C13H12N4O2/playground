namespace ChatClient
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this._btnSend = new System.Windows.Forms.Button();
            this._textBoxSend = new System.Windows.Forms.TextBox();
            this._gridControlChatHistory = new DevExpress.XtraGrid.GridControl();
            this._gridViewChatHistory = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.UID = new DevExpress.XtraGrid.Columns.GridColumn();
            this.Chat = new DevExpress.XtraGrid.Columns.GridColumn();
            ((System.ComponentModel.ISupportInitialize)(this._gridControlChatHistory)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._gridViewChatHistory)).BeginInit();
            this.SuspendLayout();
            // 
            // _btnSend
            // 
            this._btnSend.Font = new System.Drawing.Font("Monaco", 9F);
            this._btnSend.Location = new System.Drawing.Point(480, 214);
            this._btnSend.Name = "_btnSend";
            this._btnSend.Size = new System.Drawing.Size(75, 23);
            this._btnSend.TabIndex = 0;
            this._btnSend.Text = "Send";
            this._btnSend.UseVisualStyleBackColor = true;
            this._btnSend.Click += new System.EventHandler(this._btnSend_Click);
            // 
            // _textBoxSend
            // 
            this._textBoxSend.Font = new System.Drawing.Font("Monaco", 9F);
            this._textBoxSend.Location = new System.Drawing.Point(32, 216);
            this._textBoxSend.Name = "_textBoxSend";
            this._textBoxSend.Size = new System.Drawing.Size(442, 22);
            this._textBoxSend.TabIndex = 1;
            // 
            // _gridControlChatHistory
            // 
            this._gridControlChatHistory.Cursor = System.Windows.Forms.Cursors.Default;
            this._gridControlChatHistory.Font = new System.Drawing.Font("Monaco", 9F);
            this._gridControlChatHistory.Location = new System.Drawing.Point(32, 10);
            this._gridControlChatHistory.MainView = this._gridViewChatHistory;
            this._gridControlChatHistory.Name = "_gridControlChatHistory";
            this._gridControlChatHistory.Size = new System.Drawing.Size(523, 200);
            this._gridControlChatHistory.TabIndex = 2;
            this._gridControlChatHistory.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this._gridViewChatHistory});
            // 
            // _gridViewChatHistory
            // 
            this._gridViewChatHistory.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.UID,
            this.Chat});
            this._gridViewChatHistory.GridControl = this._gridControlChatHistory;
            this._gridViewChatHistory.Name = "_gridViewChatHistory";
            this._gridViewChatHistory.OptionsMenu.EnableColumnMenu = false;
            this._gridViewChatHistory.OptionsPrint.PrintHeader = false;
            this._gridViewChatHistory.OptionsView.ShowColumnHeaders = false;
            this._gridViewChatHistory.OptionsView.ShowGroupPanel = false;
            this._gridViewChatHistory.OptionsView.ShowIndicator = false;
            this._gridViewChatHistory.CustomDrawCell += new DevExpress.XtraGrid.Views.Base.RowCellCustomDrawEventHandler(this._gridViewChatHistory_CustomDrawCell);
            // 
            // UID
            // 
            this.UID.Caption = "UID";
            this.UID.FieldName = "UID";
            this.UID.Name = "UID";
            this.UID.OptionsColumn.AllowEdit = false;
            this.UID.OptionsEditForm.UseEditorColRowSpan = false;
            this.UID.Visible = true;
            this.UID.VisibleIndex = 0;
            // 
            // Chat
            // 
            this.Chat.AppearanceCell.Font = new System.Drawing.Font("Monaco", 9F);
            this.Chat.AppearanceCell.Options.UseFont = true;
            this.Chat.Caption = "Chat";
            this.Chat.FieldName = "Chat";
            this.Chat.Name = "Chat";
            this.Chat.OptionsColumn.AllowEdit = false;
            this.Chat.Visible = true;
            this.Chat.VisibleIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 261);
            this.Controls.Add(this._gridControlChatHistory);
            this.Controls.Add(this._textBoxSend);
            this.Controls.Add(this._btnSend);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this._gridControlChatHistory)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._gridViewChatHistory)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button _btnSend;
        private System.Windows.Forms.TextBox _textBoxSend;
        private DevExpress.XtraGrid.GridControl _gridControlChatHistory;
        private DevExpress.XtraGrid.Views.Grid.GridView _gridViewChatHistory;
        private DevExpress.XtraGrid.Columns.GridColumn Chat;
        private DevExpress.XtraGrid.Columns.GridColumn UID;
    }
}

