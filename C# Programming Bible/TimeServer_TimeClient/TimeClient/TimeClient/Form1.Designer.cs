namespace TimeClient
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
            this._labelCurTime = new System.Windows.Forms.Label();
            this._labelServerIP = new System.Windows.Forms.Label();
            this._textBoxCurTime = new System.Windows.Forms.TextBox();
            this._textBoxServerIP = new System.Windows.Forms.TextBox();
            this._btnConnect = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // _labelCurTime
            // 
            this._labelCurTime.AutoSize = true;
            this._labelCurTime.Font = new System.Drawing.Font("Monaco", 9F);
            this._labelCurTime.Location = new System.Drawing.Point(42, 23);
            this._labelCurTime.Name = "_labelCurTime";
            this._labelCurTime.Size = new System.Drawing.Size(62, 15);
            this._labelCurTime.TabIndex = 0;
            this._labelCurTime.Text = "현재 시간";
            // 
            // _labelServerIP
            // 
            this._labelServerIP.AutoSize = true;
            this._labelServerIP.Font = new System.Drawing.Font("Monaco", 9F);
            this._labelServerIP.Location = new System.Drawing.Point(42, 103);
            this._labelServerIP.Name = "_labelServerIP";
            this._labelServerIP.Size = new System.Drawing.Size(105, 15);
            this._labelServerIP.TabIndex = 1;
            this._labelServerIP.Text = "타임 서버 아이피";
            // 
            // _textBoxCurTime
            // 
            this._textBoxCurTime.Location = new System.Drawing.Point(45, 51);
            this._textBoxCurTime.Name = "_textBoxCurTime";
            this._textBoxCurTime.Size = new System.Drawing.Size(200, 21);
            this._textBoxCurTime.TabIndex = 2;
            // 
            // _textBoxServerIP
            // 
            this._textBoxServerIP.Location = new System.Drawing.Point(45, 131);
            this._textBoxServerIP.Name = "_textBoxServerIP";
            this._textBoxServerIP.Size = new System.Drawing.Size(200, 21);
            this._textBoxServerIP.TabIndex = 2;
            // 
            // _btnConnect
            // 
            this._btnConnect.Font = new System.Drawing.Font("Monaco", 12F);
            this._btnConnect.Location = new System.Drawing.Point(45, 167);
            this._btnConnect.Name = "_btnConnect";
            this._btnConnect.Size = new System.Drawing.Size(200, 59);
            this._btnConnect.TabIndex = 3;
            this._btnConnect.Text = "접속";
            this._btnConnect.UseVisualStyleBackColor = true;
            this._btnConnect.Click += new System.EventHandler(this._btnConnect_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this._btnConnect);
            this.Controls.Add(this._textBoxServerIP);
            this.Controls.Add(this._textBoxCurTime);
            this.Controls.Add(this._labelServerIP);
            this.Controls.Add(this._labelCurTime);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label _labelCurTime;
        private System.Windows.Forms.Label _labelServerIP;
        private System.Windows.Forms.TextBox _textBoxCurTime;
        private System.Windows.Forms.TextBox _textBoxServerIP;
        private System.Windows.Forms.Button _btnConnect;
    }
}

