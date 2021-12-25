namespace ChatServer
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
            DevExpress.XtraGrid.GridLevelNode gridLevelNode1 = new DevExpress.XtraGrid.GridLevelNode();
            this._btnSave = new System.Windows.Forms.Button();
            this._gridControlChatHistory = new DevExpress.XtraGrid.GridControl();
            this._gridViewChatHistory = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.UID = new DevExpress.XtraGrid.Columns.GridColumn();
            this.Chat = new DevExpress.XtraGrid.Columns.GridColumn();
            ((System.ComponentModel.ISupportInitialize)(this._gridControlChatHistory)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._gridViewChatHistory)).BeginInit();
            this.SuspendLayout();
            // 
            // _btnSave
            // 
            this._btnSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this._btnSave.Location = new System.Drawing.Point(881, 526);
            this._btnSave.Name = "_btnSave";
            this._btnSave.Size = new System.Drawing.Size(75, 23);
            this._btnSave.TabIndex = 0;
            this._btnSave.Text = "Save";
            this._btnSave.UseVisualStyleBackColor = true;
            this._btnSave.Click += new System.EventHandler(this._btnSave_Click);
            // 
            // _gridControlChatHistory
            // 
            this._gridControlChatHistory.Cursor = System.Windows.Forms.Cursors.Default;
            gridLevelNode1.RelationName = "Level1";
            this._gridControlChatHistory.LevelTree.Nodes.AddRange(new DevExpress.XtraGrid.GridLevelNode[] {
            gridLevelNode1});
            this._gridControlChatHistory.Location = new System.Drawing.Point(12, 12);
            this._gridControlChatHistory.MainView = this._gridViewChatHistory;
            this._gridControlChatHistory.Name = "_gridControlChatHistory";
            this._gridControlChatHistory.Size = new System.Drawing.Size(960, 508);
            this._gridControlChatHistory.TabIndex = 1;
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
            this._gridViewChatHistory.OptionsView.ShowGroupPanel = false;
            this._gridViewChatHistory.OptionsView.ShowIndicator = false;
            this._gridViewChatHistory.CustomDrawCell += new DevExpress.XtraGrid.Views.Base.RowCellCustomDrawEventHandler(this._gridViewChatHistory_CustomDrawCell);
            // 
            // UID
            // 
            this.UID.AppearanceCell.Options.UseTextOptions = true;
            this.UID.AppearanceCell.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.UID.Caption = "UID";
            this.UID.FieldName = "UID";
            this.UID.Name = "UID";
            this.UID.OptionsColumn.AllowEdit = false;
            this.UID.Visible = true;
            this.UID.VisibleIndex = 0;
            this.UID.Width = 320;
            // 
            // Chat
            // 
            this.Chat.Caption = "Chat";
            this.Chat.FieldName = "Chat";
            this.Chat.Name = "Chat";
            this.Chat.OptionsColumn.AllowEdit = false;
            this.Chat.Visible = true;
            this.Chat.VisibleIndex = 1;
            this.Chat.Width = 638;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(984, 561);
            this.Controls.Add(this._gridControlChatHistory);
            this.Controls.Add(this._btnSave);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this._gridControlChatHistory)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._gridViewChatHistory)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button _btnSave;
        private DevExpress.XtraGrid.GridControl _gridControlChatHistory;
        private DevExpress.XtraGrid.Views.Grid.GridView _gridViewChatHistory;
        private DevExpress.XtraGrid.Columns.GridColumn UID;
        private DevExpress.XtraGrid.Columns.GridColumn Chat;
    }
}

