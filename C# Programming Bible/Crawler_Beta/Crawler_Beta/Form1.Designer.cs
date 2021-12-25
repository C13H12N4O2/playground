namespace Crawler_Beta
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
            this._labelIllustID = new System.Windows.Forms.Label();
            this._textBoxIllustID = new System.Windows.Forms.TextBox();
            this._btnSelectFolder = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this._listViewImg = new System.Windows.Forms.ListView();
            this._labelDirectory = new System.Windows.Forms.Label();
            this._folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.label1 = new System.Windows.Forms.Label();
            this._downloadImg = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // _labelIllustID
            // 
            this._labelIllustID.AutoSize = true;
            this._labelIllustID.Font = new System.Drawing.Font("Monaco", 9F);
            this._labelIllustID.Location = new System.Drawing.Point(56, 40);
            this._labelIllustID.Name = "_labelIllustID";
            this._labelIllustID.Size = new System.Drawing.Size(70, 15);
            this._labelIllustID.TabIndex = 0;
            this._labelIllustID.Text = "Illust ID";
            // 
            // _textBoxIllustID
            // 
            this._textBoxIllustID.Font = new System.Drawing.Font("Monaco", 9F);
            this._textBoxIllustID.Location = new System.Drawing.Point(58, 69);
            this._textBoxIllustID.Name = "_textBoxIllustID";
            this._textBoxIllustID.Size = new System.Drawing.Size(218, 22);
            this._textBoxIllustID.TabIndex = 1;
            // 
            // _btnSelectFolder
            // 
            this._btnSelectFolder.Font = new System.Drawing.Font("Monaco", 9F);
            this._btnSelectFolder.Location = new System.Drawing.Point(58, 170);
            this._btnSelectFolder.Name = "_btnSelectFolder";
            this._btnSelectFolder.Size = new System.Drawing.Size(218, 23);
            this._btnSelectFolder.TabIndex = 2;
            this._btnSelectFolder.Text = "Browse To Select Folder";
            this._btnSelectFolder.UseVisualStyleBackColor = true;
            this._btnSelectFolder.Click += new System.EventHandler(this._btnSelectFolder_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Monaco", 9F);
            this.label2.Location = new System.Drawing.Point(56, 118);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(133, 15);
            this.label2.TabIndex = 3;
            this.label2.Text = "Download Directory";
            // 
            // _listViewImg
            // 
            this._listViewImg.Font = new System.Drawing.Font("Monaco", 9F);
            this._listViewImg.Location = new System.Drawing.Point(58, 232);
            this._listViewImg.Name = "_listViewImg";
            this._listViewImg.Size = new System.Drawing.Size(218, 162);
            this._listViewImg.TabIndex = 5;
            this._listViewImg.UseCompatibleStateImageBehavior = false;
            // 
            // _labelDirectory
            // 
            this._labelDirectory.AutoSize = true;
            this._labelDirectory.Font = new System.Drawing.Font("Monaco", 9F);
            this._labelDirectory.Location = new System.Drawing.Point(56, 144);
            this._labelDirectory.Name = "_labelDirectory";
            this._labelDirectory.Size = new System.Drawing.Size(0, 15);
            this._labelDirectory.TabIndex = 6;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "label1";
            // 
            // _downloadImg
            // 
            this._downloadImg.Font = new System.Drawing.Font("Monaco", 9F);
            this._downloadImg.Location = new System.Drawing.Point(58, 199);
            this._downloadImg.Name = "_downloadImg";
            this._downloadImg.Size = new System.Drawing.Size(218, 23);
            this._downloadImg.TabIndex = 2;
            this._downloadImg.Text = "Download";
            this._downloadImg.UseVisualStyleBackColor = true;
            this._downloadImg.Click += new System.EventHandler(this._downloadImg_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(342, 421);
            this.Controls.Add(this.label1);
            this.Controls.Add(this._labelDirectory);
            this.Controls.Add(this._listViewImg);
            this.Controls.Add(this.label2);
            this.Controls.Add(this._downloadImg);
            this.Controls.Add(this._btnSelectFolder);
            this.Controls.Add(this._textBoxIllustID);
            this.Controls.Add(this._labelIllustID);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label _labelIllustID;
        private System.Windows.Forms.TextBox _textBoxIllustID;
        private System.Windows.Forms.Button _btnSelectFolder;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListView _listViewImg;
        private System.Windows.Forms.Label _labelDirectory;
        private System.Windows.Forms.FolderBrowserDialog _folderBrowserDialog;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button _downloadImg;
    }
}

